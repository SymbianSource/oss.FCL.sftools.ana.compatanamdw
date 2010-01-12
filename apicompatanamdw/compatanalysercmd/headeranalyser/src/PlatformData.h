/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies). 
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  
*
*/


#ifndef PLATFORMDATA_H
#define PLATFORMDATA_H

#include <xercesc/dom/DOM.hpp>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Component;
class PlatformData;

typedef vector<string> IncludePaths;

#define PLATFORM_ELEMENT_COMPONENT      "component"
#define PLATFORM_ELEMENT_HEADER         "hdr"
#define PLATFORM_ELEMENT_PROJECT        "prj"
#define PLATFORM_ELEMENT_SOURCE         "src"
#define PLATFORM_ELEMENT_FILENAME       "fname"
#define PLATFORM_ELEMENT_RELPATH        "path"
#define PLATFORM_ELEMENT_INCLUDEPATH    "incpath"
#define PLATFORM_ELEMENT_INCLUDE        "inc"
#define PLATFORM_ELEMENT_FORCEDINCLUDE  "finc"
#define PLATFORM_IGNORED_COMPONENT     "excluded header list"
#define PLATFORM_ELEMENT_API_NAME      "api"
/**
 * Abstract base class for all the elements that are parsed from the 
 * platform's XML description.
 */
class ParsedElement
{
public:
    ParsedElement();
    virtual ~ParsedElement();

    /**
     * Initializes the element. This must be called before finalizing the element.
     * @param node Pointer to the DOM node containing the data for the element.
     * @param platform Pointer to the platform in which this element belongs.
     * @return true if the initialization was successful, false otherwise.
     */
    virtual bool Initialize(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node, PlatformData* platform);
    
    /**
     * For debugging purposes. Prints the data of an element to standard output.
     * @param indentSpaces Number of indentation spaces to get hierarchical print.
     * @return string object containing the element's data.
     */
    virtual string PrettyPrint(int indentSpaces = 0) const = 0;

protected:

    /**
     * Processes the attributes of an XML element.
     * @param node Pointer to the element's DOM data.
     */
    virtual void ProcessAttributes(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node) = 0;

    /**
     * Processes the child elements of an XML element.
     * @param node Pointer to the element's DOM data.
     * @param platform Pointer to the platform in which this element belongs.
     */
    virtual bool ProcessChildElement(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node, PlatformData* platform) = 0;

    /**
     * Adds this element to the given platform. NOTE! When the addition
     * is successful, the platform takes the ownership of this element.
     * But when the addition is unsuccessful the caller must take care of
     * the object deallocation.
     * @param platform Pointer to the platform
     * @return true, if the addition was successful. False otherwise. 
     */
    virtual bool AddToPlatform(PlatformData* platform) = 0;

    // Platform's root directory. Given in application parameters (i.e BASELINEDIR or CURRENTDIR).
    string iRootDir;
};

typedef vector<ParsedElement*> ElementVector;

/**
 * ComponentFile is a base class for files inside a component.
 */
class ComponentFile : public ParsedElement
{
public:
    
    /**
     * Default constructor
     */
    ComponentFile();

    /**
     * Constructor
     * @param ID Unique file id.
     * @param comp Pointer to the <code>Component</code> in which this file belongs.
     */
    ComponentFile(const string& ID, Component* comp);

    /**
     * Copy constructor
     * @param rhs Reference to the <code>ComponentFile</code> from which the data is copied.
     */
    ComponentFile(const ComponentFile& rhs);

    /**
     * Destructor
     */
    virtual ~ComponentFile();
    
    /**
     * Returns the file id.
     * @return Reference to a <code>string</code> object representing the file id.
     */
    virtual const string& ID() const;

    /**
     * Returns the file name.
     * @return Reference to a <code>string</code> object representing the file name.
     */
    virtual const string& FileName() const;        

    /**
     * Returns the path of the file.
     * @return Reference to a <code>string</code> object representing the path.
     */
    virtual const string& Path() const;
    
    /**
     * Sets the file id.
     * @param ID Reference to a <code>string</code> represeting the file id.
     */
    virtual void SetID(const string& ID);

    /**
     * Sets the file name.
     * @param name Reference to a <code>string</code> represeting the file name.
     */
    virtual void SetFileName(const string& name);

    /**
     * Sets the path.
     * @param path Reference to a <code>string</code> represeting the path.
     */
    virtual void SetPath(const string& path);

    /**
     * Returns the owner component.
     * @return Pointer to the component in which this file belongs.
     */
    virtual Component* GetComponent() const;

    /**
     * Sets the owner component.
     * Pointer to the <code>Component</code> object. Does not take the ownership.
     */
    virtual void SetComponent(Component* comp);

    /**
     * Assignment operator
     */
    virtual const ComponentFile& operator= (const ComponentFile& rhs);

    /**
     * Comparison operator
     */
    virtual bool operator== (const ComponentFile& rhs) const;

    /**
     * Returns the include directives defined for this element
     * @return Reference to the <code>std::vector</code> containing include directives
     */
    virtual const vector<string>& Includes() const;

    /**
     * Adds include directive (string) to the object
     * @param incHdr name of the header to be included
     */
    virtual void AddInclude(const string& incHdr);

    /**
     * Adds include directives to the object
     * @param incs Reference to the <code>std::vector</code> containing the include directives.
     */
    virtual void SetIncludes(const vector<string>& incs);

    /**
     * Returns the include paths used in compilation of the project
     * @return Reference to a <code>vector</code> containing <code>string</code>
     * objects that represent the include paths.
     */
    const vector<string>& IncludePaths() const;

    /**
     * Adds an include path
     * @param incPath Reference to a <code>string</code> object representing
     * the include path.
     */
    void AddIncludePath(const string& incPath);   
    
    
    /**
     * Returns the forced include used in compilation of the component
     * @return a string object representing the forced include.
     */
    string ForcedInclude();
	
	/**
     * Returns pair of string , with API name and category
     */
	pair<string,string>& APIinfo();
    
protected:

    // From ParsedElement:
    virtual void ProcessAttributes(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node);
    virtual bool ProcessChildElement(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node, PlatformData* platform);

    string iID; // File id
    string iName; // File name
    string iPath; // Path
	pair<string,string> iApiInfo; // API info for the header
    Component* iComponent; // Component, does not own the pointer
    vector<string> iIncludes; // Include directives
    vector<string> iIncludePaths; // Include paths
    string iForcedInclude; // Forced include
};

typedef vector<ComponentFile*> FileList;

/**
 * This class represents the project. Project belongs to one component and
 * has a list of include and source paths as well as the source files 
 * belonging to the project.
 */
class Project : public ComponentFile
{
public:

    /**
     * Default constructor
     */
    Project();
    
    /**
     * Constructor
     * @param prjID Project file id
     * @param comp Pointer to the <code>Component</code> object in which 
     * this project belongs.
     */
    Project(const string& prjID, Component* comp);

    /**
     * Destructor
     */
    virtual ~Project();

    /**
     * Returns the list of <code>Source</code> objects contained by this project
     * @return Reference to the list of <code>Source</code> objects.
     */
    const FileList& Sources() const;    

    // From ParsedElement:    
    virtual string PrettyPrint(int indentSpaces = 0) const;

protected:

    // From ParsedElement:
    virtual bool AddToPlatform(PlatformData* platform);    
    virtual bool ProcessChildElement(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node, PlatformData* platform);
    FileList iSourceObjs; // Source objects belonging to this project
};


/**
 * This class represents the header file, which belongs to one component.
 * It has a analysis status telling whether the header should be ignored
 * from the analysis or it is just being analyzed or the analysis is ready.
 */
class Header : public ComponentFile
{
public:
    
    enum STATUS {
        HDR_STATUS_UNDEF = 0, // Undefined status
        HDR_STATUS_IGNORE, // Header should be ignored from the analysis
        HDR_STATUS_TO_BE_ANALYZED, // Header will be analyzed
        HDR_STATUS_READY, // Analysis for the header is ready
        HDR_STATUS_INVALID,// Invalid header
        HDR_STATUS_FAILED // Analysis and/or compilation failed
    };

    /**
     * Default constructor
     */
    Header();

    /**
     * Constructor
     * @param hdrID Header file id
     * @param comp Pointer to the component in which this header belongs.
     */
    Header(const string& hdrID, Component* comp);

    /**
     * Destructor
     */
    virtual ~Header();

    /**
     * Returns the status of the header
     * @return Status of the header
     */
    STATUS Status() const;

    /**
     * Sets the status of the header
     * @param s Status of the header.
     */
    void SetStatus(STATUS s);

    // From ParsedElement:    
    virtual string PrettyPrint(int indentSpaces = 0) const;  

    /**
     * Returns pointer to the cached include directives. Once the include directives
     * are fetched by <code>PlatformData</code>, they are cached for further use to
     * speed up the analysis.
     *
     * @return Pointer to the <code>std::vector</code> containing cached include
     * directives
     */
    const vector<string>* CachedIncludes() const;

    /**
     * Returns pointer to the cached include paths. Once the include paths
     * are fetched by <code>PlatformData</code>, they are cached for further use to
     * speed up the analysis.
     *
     * @return Pointer to the <code>std::vector</code> containing cached include
     * paths
     */
    const vector<string>* CachedIncludePaths() const;
    
    /**
     * Returns the cached forced include directive. Once the forced include directive
     * is fetched by <code>PlatformData</code>, it is cached for further use to
     * speed up the analysis.
     *
     * @return cached forced include
     * directives
     */
    string CachedForcedInclude() const;

	 /**
     * Returns the cached source object for the header. 
     */
	string CachedSource() const;
	

    /** 
     * Sets cached include directives. Takes the ownership of the given pointer.
     * @param Pointer to the include directives
     */
    void SetCachedIncludes(vector<string>* incs);

    /** 
     * Sets cached include paths. Takes the ownership of the given pointer.
     * @param Pointer to the include directives
     */
    void SetCachedIncludePaths(vector<string>* incPaths);
    
    /** 
     * Sets cached forced include directive.
     * @param Forced include directive
     */
    void SetCachedForcedInclude(string finc);

	/** 
     * Sets cached soource file.
     * @param source File
     */
	void SetCachedSourceFile (string srcObj);

protected:

    // From ParsedElement:
    virtual void ProcessAttributes(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node);    
    virtual bool AddToPlatform(PlatformData* platform);        

private:
    STATUS iStatus; // Header's status
    vector<string>* iCachedIncludes; // Cached additional include directives. Owns the pointer!!
    vector<string>* iCachedIncludePaths; // Cached include paths. Owns the pointer!!
    string iCachedForcedInclude; // Cached forced include.
	string iCacheSrcObj;
};

/**
 * This class represents the source file belonging to a component.
 * It has a list of include directives.
 */
class Source : public ComponentFile
{
public:

    /**
     * Default constructor
     */
    Source();

    /**
     * Constructor
     * @param srcID Source file id
     * @param comp Pointer to the component
     */
    Source(const string& srcID, Component* comp);

    /**
     * Destructor
     */
    virtual ~Source();

    // From ParsedElement:    
    virtual string PrettyPrint(int indentSpaces = 0) const;

protected:
    // From ParsedElement:
    virtual bool AddToPlatform(PlatformData* platform);        
};

/**
 * Component
 */
class Component : public ComponentFile
{
public:
    /**
     * Default constructor
     */
    Component();

    /**
     * Constructor
     * @param compID Unique component ID
     */
    Component(const string& compID, Component* comp);

    /**
     * Destructor
     */
    virtual ~Component();
    
    /**
     * Returns the header objects belonging to this component.
     * @return Header objects.
     */
    const FileList& Headers() const;

    /**
     * Returns the header objects belonging to this component.
     * @return Header objects.
     */
    FileList& Headers();

    /**
     * Returns the project objects belonging to this component.
     * @return Project objects.
     */
    const FileList& Projects() const;

    /**
     * Returns the project objects belonging to this component.
     * @return Project objects.
     */
    FileList& Projects();

    /**
     * Adds <code>Header</code> object to the component
     * @param hdr Pointer to the <code>Header</code> object.
     */
    void AddHeader(ComponentFile* hdr); 

    /**
     * Adds <code>Project</code> object to the component
     * @param hdr Pointer to the <code>Project</code> object.
     */
    void AddProject(ComponentFile* prj);
    
    // From ParsedElement:    
    virtual string PrettyPrint(int indentSpaces = 0) const;
    
protected:
    // From ParsedElement:
    virtual bool AddToPlatform(PlatformData* platform);   
    virtual bool ProcessChildElement(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node, PlatformData* platform);
        
    FileList iHeaders; // Header objects
    FileList iProjects; // Project objects
};

typedef map<string, ComponentFile*> CFileMap;
typedef map<string, Component*> ComponentList;

/**
 * PlatformData class represents the platform specific data that is needed
 * in compilation of platform's header files.
 * This class contains methods that offer different views to the platform data
 * in order to enable efficient data processing for the clients.
 */
class PlatformData
{
public:

    /**
     * Constructor
     * @param pfVersion Platform version given in application parameters.
     * @param rootDir Platform's root directory given in application parameters.
     */
    PlatformData(const string& pfVersion, const string& rootDir);

    /**
     * Destructor
     */
    virtual ~PlatformData();

    /**
     * Initializes the platform data. This method reads and parses the 
     * platform data from the given file and sorts the data in private
     * containers for later use. 
     * @param dataFileName Platform data file name.
     */
    void Initialize(const string& dataFileName);

    /**
     * Returns headers sorted by their file ids.
     * @return Reference to the <code>CFileMap</code> object containing the
     * headers sorted by their file ids.
     */
    const CFileMap& HeadersById() const;    
    
    /**
     * Returns headers having the given status sorted by their file ids.
     * @param hdrStatus Header status. All the headers having this status 
     * are returned.
     * @param Reference to the <code>CFileMap</code> object in which the
     * the headers matching the hdrStatus are returned.
     */
    void HeadersByStatus(Header::STATUS hdrStatus, CFileMap& hdrFiles) const;

    /**
     * Returns projects sorted by their file ids.
     * @return Reference to the <code>CFileMap</code> object containing the
     * projects sorted by their file ids.
     */
    const CFileMap& ProjectsById() const;

    /**
     * Returns projects sorted by their file ids.
     * @return Reference to the <code>CFileMap</code> object containing the
     * projects sorted by their file ids.
     */
    CFileMap& ProjectsById();

    /**
     * Returns sources sorted by their file ids.
     * @return Reference to the <code>CFileMap</code> object containing the
     * sources sorted by their file ids.
     */
    const CFileMap& SourcesById() const;

    /**
     * Gets include paths needed in compilation of the given header
     * @param headerID ID of the header file.
     * @param incPaths Include paths needed in compilation of the header.
     */
    const vector<string>& IncludePathsForHeader(const string& headerID);

    /**
     * Gets include paths needed in compilation of the given header
     * @param headerObj Pointer to the header file object.
     * @param incPaths Include paths needed in compilation of the header.
     */
    const vector<string>& IncludePathsForHeader(Header* headerObj);

    /**
     * Gets additional include directives needed in compilation of the given header
     * @param headerID ID of the header file.
     * @param incs Include directives needed in compilation of the header.
     */
    const vector<string>& IncludesForHeader(const string& headerID);

    /**
     * Gets additional include directives needed in compilation of the given header
     * @param headerObj Pointer to the header file object.
     * @param incs Include directives needed in compilation of the header.
     */
    const vector<string>& IncludesForHeader(Header* headerObj, Header* baseHObj = NULL);

    /**
     * Adds component to the component list. Takes the ownership of the pointer.
     * @param comp Pointer to the <code>Component</code> object.
     */
    bool AddComponent(Component* comp);

    /**
     * Adds project to the project list. Takes the ownership of the pointer.
     * @param prj Pointer to the <code>Project</code> object.
     */
    bool AddProject(Project* prj);

    /**
     * Adds header to the header list. Takes the ownership of the pointer.
     * @param hdr Pointer to the <code>Header</code> object.
     */
    bool AddHeader(Header* hdr);

    /**
     * Adds source to the source list. Takes the ownership of the pointer.
     * @param src Pointer to the <code>Source</code> object.
     */
    bool AddSource(Source* src);

    /**
     * Factory method creating correct element type for the given <code>DOMNode</code>.
     * @param node Pointer to the <code>DOMNode</code>.
     * @return Pointer to the created object.
     */
    ParsedElement* CreateElement( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node );

    /**
     * Returns the list of components
     * @return Reference to the component list
     */
    const ComponentList& Components() const;

    /**
     * Prints the elements read from the platform data file.
     * For debugging purposes.
     * @return string representing the platform data.
     */
    string PrettyPrint() const;

    /**
     * Returns the root directory of the platform.
     * @return Root directory string
     */
    const string& GetRootDir() const;

private:
    void IncludesFromSource(const Header* hObj, const Source* srcObj, vector<string>& includes) const;
    vector<string> iDummyStringVector;    
    void InitializeElements();    
    ComponentList iCList; // All components in platform
    CFileMap iHeadersById; // All headers in platform
    CFileMap iSourcesById; // All sources in platform
    CFileMap iProjectsById; // All projects in platform
        
    // Pointer to DOMBuilder
    XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder* iDOMParser;
    // Pointer to DOMDocument
    XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* iDOMDoc;
    // Pointer to DOM root node
    XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* iDOMRootElement;

    string iRootDir; // Root directory
    string iPfVersion; // Version string given in constructor.
    string iVersionStr; // Read from the XML-file (versionid attribute)
};

#endif
