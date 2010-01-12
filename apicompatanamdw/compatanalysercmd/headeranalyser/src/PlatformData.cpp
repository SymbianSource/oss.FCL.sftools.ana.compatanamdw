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


#include "CmdGlobals.h"
#ifdef __WIN__
#pragma warning(disable:4786)
#endif

#include <vector>
#include <algorithm>
#include "PlatformData.h"
#include "XMLUtils.h"
#include "XMLStringConst.h"
#include "Utils.h"
#include "BBCFileUtils.h"
#include "HAException.h"


const char* XML_FILE_ID_ATTRIBUTE = "id";

/**
 * Generic utility function, which checks whether the given object is
 * in the vector.
 */
template <typename C>
inline bool IsObjectInVector(const vector<C>& v, const C& o)
{ 
    return std::find(v.begin(), v.end(), o) != v.end();
}

// Convert to proper dir-separator
string& FixPathString(string& str)
{
    string::size_type dirSepInd = str.find_first_of("\\/");
    if( dirSepInd != string::npos && str.at(dirSepInd) != DIR_SEPARATOR )
    {        
        replaceChar(str, str.at(dirSepInd), DIR_SEPARATOR);
    }
    return str;
}

/**
 *
 */
ComponentFile::ComponentFile()
:
iComponent(0)
{}

/**
 *
 */
ComponentFile::ComponentFile(const string& ID, Component* comp)
: 
iID(ID),
iComponent(comp)
{ }

/**
 *
 */
ComponentFile::ComponentFile(const ComponentFile &rhs)
:
iID(rhs.ID()),
iName(rhs.FileName()),
iPath(rhs.Path()),
iComponent(rhs.GetComponent())
{ }

/**
 *
 */
ComponentFile::~ComponentFile()
{ }

/**
 *
 */
const string& ComponentFile::ID() const
{
    return iID;
}

/**
 *
 */
const string& ComponentFile::FileName() const
{
    return iName;
}

/**
 *
 */
const string& ComponentFile::Path() const
{
    return iPath;
}

/**
 *
 */
void ComponentFile::SetID(const string& ID)
{
    iID = ID;
}

/**
 *
 */
void ComponentFile::SetFileName(const string& name)
{
    iName = name;
}

/**
 *
 */
void ComponentFile::SetPath(const string& path)
{
    iPath = path;
}

/**
 *
 */
Component* ComponentFile::GetComponent() const
{
    return iComponent;
}

/**
 *
 */
void ComponentFile::SetComponent(Component* comp)
{
    iComponent = comp;
}

/**
 *
 */
string ComponentFile::ForcedInclude()
{
return iForcedInclude;
}

pair<string,string>& ComponentFile::APIinfo()
{
    return iApiInfo;
}

/**
 *
 */
const ComponentFile& ComponentFile::operator= (const ComponentFile& rhs)
{
    if( &rhs != this )
    {
        iID = rhs.ID();
        iName = rhs.FileName();
        iPath = rhs.Path();
        iComponent = rhs.GetComponent();
    }
    return *this;
}

/**
 *
 */
bool ComponentFile::operator== (const ComponentFile& rhs) const
{
    return  iID == rhs.ID() &&
//            iName == rhs.iName &&
//            iPath == rhs.iPath &&
            iComponent == iComponent;
}

/**
 *
 */
void ComponentFile::ProcessAttributes(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node)
{
    // Read "fileid"-attribute:
    const XMLCh* fileIdAttr = GetAttribute(node, XML_FILE_ID_ATTRIBUTE);
    if( fileIdAttr )
    {
        string str(toString(fileIdAttr));
        iID = FixPathString(toLower(str));        
    }
}

/**
 * Reads child elements from the parsed XML (DOM) data. This baseclass implementation
 * processes the "filename", "relativepath" and "include" elements, which are common 
 * to all component files.
 */
bool ComponentFile::ProcessChildElement(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node, PlatformData* platform)
{    
    if( node->getNodeType() != DOMNode::ELEMENT_NODE )
        return false;

    bool properChild = false;

    const XMLCh* elementtype = node->getNodeName();
    if( elementtype )
    {
        string elemtypeStr(toString(elementtype));

		//Handle the API info.
		if( elemtypeStr == PLATFORM_ELEMENT_API_NAME )
        {
			XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* apiNode = (DOMElement*)node;
			char* apiname = _X( apiNode->getAttribute( _X( "name" ) ) );
			char* apiCategory = _X( apiNode->getAttribute( _X( "category" ) ) );

			iApiInfo.first = apiname;
			iApiInfo.second = apiCategory;

			_XX(apiname);
			_XX(apiCategory);
        }
        if( elemtypeStr == PLATFORM_ELEMENT_INCLUDE )
        {
            // Handle include element
            const XMLCh* nodeVal = node->getTextContent();
            if( nodeVal )
            {
                string tempStr(toString(nodeVal));
                iIncludes.push_back(FixPathString(toLower(tempStr)));
                properChild = true;
            }
        }
        else if( elemtypeStr == PLATFORM_ELEMENT_INCLUDEPATH )
        {
            // Include paths:
            const XMLCh* nodeVal = node->getTextContent();
            if( nodeVal )
            {
                string tempStr(toString(nodeVal));
                iIncludePaths.push_back(FixPathString(toLower(tempStr)));                
                properChild = true;
            }
        }
        else if( elemtypeStr == PLATFORM_ELEMENT_FORCEDINCLUDE )
        {
            // Forced Include:
            const XMLCh* nodeVal = node->getTextContent();
            if( nodeVal )
            {
                iForcedInclude=toString(nodeVal);
                properChild = true;
            }
        }
    }
    return properChild;
}

/**
 *
 */
const vector<string>& ComponentFile::IncludePaths() const
{
    return iIncludePaths;
}

/**
 *
 */
void ComponentFile::AddIncludePath(const string& incPath)
{
    if( IsObjectInVector<string>(iIncludePaths, incPath) == false )
        iIncludePaths.push_back(incPath);
}

const vector<string>& ComponentFile::Includes() const
{
    return iIncludes;
}

void ComponentFile::AddInclude(const string& incHdr)
{
    if( IsObjectInVector<string>(iIncludes, incHdr) == false )
        iIncludes.push_back(incHdr);
}

void ComponentFile::SetIncludes(const vector<string>& incs)
{
    iIncludes = incs;
}

ParsedElement::ParsedElement()
{}

ParsedElement::~ParsedElement()
{}

/**
 * Initializes the element using parsed XML (DOM) data. This method initiates
 * attribute processing, child element processing and adds the element to
 * the platform data object.
 */
bool ParsedElement::Initialize(DOMNode* node, PlatformData* platform)
{
    if( node == 0 || platform == 0 )
        return false;

    iRootDir = platform->GetRootDir();

    // Read and process attributes of xml-element:
    ProcessAttributes(node);
                
    // Process child elements:
    DOMNodeList* childNodes = node->getChildNodes();
    XMLSize_t childListLen = 0;
    if( childNodes )
    {
        childListLen = childNodes->getLength();
        for( XMLSize_t cI = 0; cI < childListLen; ++cI )
        {
            DOMNode* childNode = childNodes->item(cI);
            if( childNode )
            {                
                ProcessChildElement(childNode, platform);                
            }
        }
    }

    // Add this element to a proper container of the platform data object:
    return AddToPlatform(platform);
}

/**
 *
 */
Project::Project()
{}

/**
 *
 */
Project::Project(const string& prjID, Component* comp) 
: ComponentFile(prjID, comp)
{ }
 
/**
 *
 */
Project::~Project()
{ }

/**
 * Adds this project element to platform's project list.
 */
bool Project::AddToPlatform(PlatformData* platform)
{
    return platform->AddProject(this);
}

/**
 * Processes the given child element. Project can have following
 * child elements:
 *  - includepath
 *  - source
 */
bool Project::ProcessChildElement(DOMNode* child, PlatformData* platform)
{   
    if( ComponentFile::ProcessChildElement(child, platform) == true )
        return true;

    bool properChild = false;
    const XMLCh* childtype = child->getNodeName();
    if( childtype )
    {
        string childtypeStr(toString(childtype));
        const XMLCh* nodeVal = child->getTextContent();
        if( nodeVal )
        {                        
            if( childtypeStr == PLATFORM_ELEMENT_SOURCE )
            {
                Source* srcObj = new Source();
                if( srcObj->Initialize(child, platform) )
                {
                    iSourceObjs.push_back(srcObj);
                    properChild = true;
                }
                else
                    delete srcObj;
            }
        }
    }
    return properChild;
}

/**
 * 
 */
const FileList& Project::Sources() const
{
    return iSourceObjs;
}

/**
 * 
 */
string Project::PrettyPrint(int indentSpaces) const
{
    string ret;
    for( int i = 0; i < indentSpaces; ++i )
    {
        ret += " ";
    }
    ret += string("Project ID: ") + iID + "\n";
    for( int i = 0; i < indentSpaces; ++i )
    {
        ret += " ";
    }
    ret += "Sources:\n";
    for( FileList::const_iterator s = iSourceObjs.begin(); s != iSourceObjs.end(); ++s )
    {
        ret += (*s)->PrettyPrint(indentSpaces+2);
    }
    return ret;
}

/**
 * Header
 */
Header::Header()
:
iCachedIncludes(0),
iCachedIncludePaths(0),
iCachedForcedInclude("")
{}
/**
 * 
 */
Header::Header(const string& hdrID, Component* comp) 
: 
ComponentFile(hdrID, comp),
iCachedIncludes(0),
iCachedIncludePaths(0),
iCachedForcedInclude("")
{ }

/**
 * 
 */
Header::~Header()
{ 
    delete iCachedIncludes;
    delete iCachedIncludePaths;
}

/**
 * 
 */
Header::STATUS Header::Status() const
{
    return iStatus;
}

/**
 * 
 */
void Header::SetStatus(Header::STATUS s)
{
    iStatus = s;
}

/**
 * 
 */
bool Header::AddToPlatform(PlatformData* platform)
{
    return platform->AddHeader(this);
}

/**
 *
 */
string Header::PrettyPrint(int indentSpaces) const
{
    string ret;
    for( int i = 0; i < indentSpaces; ++i )
    {
        ret += " ";
    }
    ret += string("Header ID: ") + iID + "\n";

    return ret;
}

void Header::ProcessAttributes(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node)
{
    /**
     * Header element uses absolute path as a key, since that way it is easier
     * to map this element to the filenames used in Analyser. Absolute path
     * is calculated merging the root directories given in parameters (i.e BASELINEDIR
     * and CURRENTDIR).
     */
    const XMLCh* fileIdAttr = GetAttribute(node, XML_FILE_ID_ATTRIBUTE);
    if( fileIdAttr )
    {
        string tempStr(toString(fileIdAttr));
        FixPathString(toLower(tempStr));
        // Merge root and element directories.
        // START -- Support for multiple header directories --
        list<pair<string, bool> > fullID = BBCFileUtils::MergeDirs(iRootDir, tempStr);
        list<pair<string, bool> >::iterator fulliterbegin = fullID.begin();
        for(; fulliterbegin != fullID.end(); fulliterbegin++)
        {
          if( fulliterbegin->second )
          {
            iID = fulliterbegin->first;
          }
        }
        // END -- Support for multiple header directories --
    }
}

/**
 * When IncludesForHeader() method of PlatformData is called, PlatformData
 * retrieves the additional include directives from all the sources in the 
 * component and caches the include directives to Header object, so next 
 * time the retrival is faster. 
 */

/**
 * 
 */
const vector<string>* Header::CachedIncludes() const
{
    return iCachedIncludes;
}

/**
 * 
 */
void Header::SetCachedIncludes(vector<string>* incs)
{
    if( iCachedIncludes )
        delete iCachedIncludes;
    iCachedIncludes = incs;
}

/**
 * When IncludesPathsForHeader() method of PlatformData is called, PlatformData
 * retrieves the include paths from all the projects in the component and 
 * caches the include paths to Header object, so next time the retrival is
 * faster.
 */

/**
 *
 */
const vector<string>* Header::CachedIncludePaths() const
{
    return iCachedIncludePaths;
}

/**
 *
 */
void Header::SetCachedIncludePaths(vector<string>* incPaths)
{
    if( iCachedIncludePaths )
        delete iCachedIncludePaths;
    iCachedIncludePaths = incPaths;
}


/**
 * When IncludesForHeader() method of PlatformData is called, PlatformData
 * retrieves the additional forced include directive from the component
 * and caches the forced include directive to Header object, so next 
 * time the retrival is faster. 
 */

/**
 * 
 */
string Header::CachedForcedInclude() const
{
    return iCachedForcedInclude;
}

string Header::CachedSource() const
{
	return iCacheSrcObj;
}

/**
 * 
 */
void Header::SetCachedForcedInclude(string finc)
{
    iCachedForcedInclude = finc;
}

void Header::SetCachedSourceFile (string srcObj)
{
	iCacheSrcObj = srcObj;
}
/**
 * Source
 */
Source::Source()
{}

/**
 * 
 */
Source::Source(const string& srcID, Component* comp) 
: ComponentFile(srcID, comp)
{ }

/**
 * 
 */
Source::~Source()
{ }

/**
 * 
 */
bool Source::AddToPlatform(PlatformData* platform)
{
    return platform->AddSource(this);
}

/**
 *
 */
string Source::PrettyPrint(int indentSpaces) const
{
    string ret;
    for( int i = 0; i < indentSpaces; ++i )
    {
        ret += " ";
    }
    ret += string("Source ID: ") + iID + "\n";
    for( int i = 0; i < indentSpaces; ++i )
    {
        ret += " ";
    }
    ret += "Include directives:\n";
    for( vector<string>::const_iterator inc = iIncludes.begin(); inc != iIncludes.end(); ++inc )
    {
        for( int i = 0; i < indentSpaces+2; ++i )
        {
            ret += " ";
        }
        ret += *inc + "\n";
    }

    return ret;
}

/**
 * Component
 */
Component::Component()
{ }

/**
 *
 */
Component::Component(const string& compID, Component* comp)
: 
ComponentFile(compID, comp)
{ }

/**
 *
 */
Component::~Component()
{ }
   
/**
 *
 */
const FileList& Component::Headers() const
{
    return iHeaders;
}

/**
 *
 */
FileList& Component::Headers()
{
    return iHeaders;
}

/**
 *
 */
const FileList& Component::Projects() const
{
    return iProjects;
}

/**
 *
 */
FileList& Component::Projects()
{
    return iProjects;
}

/**
 *
 */
void Component::AddHeader(ComponentFile* hdr)
{ 
    if( IsObjectInVector<ComponentFile*>(iHeaders, hdr) == false )
    {
        iHeaders.push_back(hdr);
    }
}

/**
 *
 */
void Component::AddProject(ComponentFile* prj)
{ 
    if( IsObjectInVector<ComponentFile*>(iProjects, prj) == false )
    {
        iProjects.push_back(prj);
    }
}

/**
 * Processes child elements. Component can have following child elements:
 *  - Header
 *  - Project reference
 */
bool Component::ProcessChildElement(DOMNode* child, PlatformData* platform)
{   
    if( ComponentFile::ProcessChildElement(child, platform) == true )
        return true;

    bool properChild = false;
    const XMLCh* childtype = child->getNodeName();
    if( childtype )
    {
        string childtypeStr(toString(childtype));
        if( childtypeStr == PLATFORM_ELEMENT_HEADER )
        {            
            Header* hdr = new Header();
			string headerID(this->ID());
            if( hdr->Initialize(child, platform) )
			{
				if(headerID == PLATFORM_IGNORED_COMPONENT )
					hdr->SetStatus(Header::HDR_STATUS_IGNORE);

				XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* hdrNode = (DOMElement*)child;
				char* headername = _X( hdrNode->getAttribute( _X( "id" ) ) );
				string header (headername);
				header = FixPathString(toLower(header)); 
				int loc = header.find_last_of(DIR_SEPARATOR);
				if(loc != -1 )
				{
					// store header file name and path from header id tag only.
					hdr->SetFileName(header.substr(loc+1,string::npos));
					hdr->SetPath(header.substr(0,loc));
				}
				_XX(headername);

				hdr->SetComponent(this);
				iHeaders.push_back(hdr);
				properChild = true;
			}
            else
            {                
                delete hdr;                
            }
        }
        else if( childtypeStr == PLATFORM_ELEMENT_PROJECT )
        {            
            Project* prj = new Project();
            if (prj->Initialize(child, platform) )
            {
                prj->SetComponent(this);
                iProjects.push_back(prj);
                properChild = true;
            }
            else
            {
                delete prj;
            }
        }       
    }
    return properChild;
}

/**
 *
 */
bool Component::AddToPlatform(PlatformData* platform)
{
    return platform->AddComponent(this);
}

/**
 *
 */
string Component::PrettyPrint(int indentSpaces) const
{
    string ret;
    for( int i = 0; i < indentSpaces; ++i )
    {
        ret += " ";
    }
    ret += string("Component ID: ") + iID + "\n";
    for( int i = 0; i < indentSpaces; ++i )
    {
        ret += " ";
    }
    ret += "Headers:\n";
    for( FileList::const_iterator h = iHeaders.begin(); h != iHeaders.end(); ++h )
    {        
        ret += (*h)->PrettyPrint(indentSpaces+2);
    }

    for( int i = 0; i < indentSpaces; ++i )
    {
        ret += " ";
    }
    ret += "Projects\n";

    for( FileList::const_iterator p = iProjects.begin(); p != iProjects.end(); ++p )
    {
        ret += (*p)->PrettyPrint(indentSpaces+2);
    }

    return ret;
}

/**
 * PlatformData contains all the elements defined in the platrofm input file.
 * It parses the XML-file and populates the internal containers. It also
 * has different kind of methods for retrieving the data and the associations
 * between elements.
 */
PlatformData::PlatformData(const string& pfVersion, const string& rootDir)
:
iDOMParser(0),
iDOMDoc(0),
iDOMRootElement(0),
iPfVersion(pfVersion),
iRootDir(rootDir)
{ }

/**
 *
 */
PlatformData::~PlatformData()
{
    if (iDOMParser != NULL)
    {
        iDOMParser->resetDocumentPool();
        iDOMParser->release();
        iDOMParser = NULL;
    }

    CFileMap::iterator i;

    for( i = iHeadersById.begin(); i != iHeadersById.end(); ++i )
    {
        delete i->second;
    }

    for( i = iProjectsById.begin(); i != iProjectsById.end(); ++i )
    {
        delete i->second;
    }

    for( i = iSourcesById.begin(); i != iSourcesById.end(); ++i )
    {
        delete i->second;
    }

    for( ComponentList::iterator ic = iCList.begin(); ic != iCList.end(); ++ic )
    {
        delete ic->second;
    }
}

/**
 *
 */
void PlatformData::Initialize(const string& dataFileName)
{
    // First read and parse the XML-file:
    int ret = 0;
    if (iDOMParser != NULL) 
    {
        iDOMParser->resetDocumentPool();
        iDOMParser->release();
        iDOMParser = 0;
    }
    cout << "Parsing platform data for " << iPfVersion << "...";
    try {
        ret = ParseXMLFile(dataFileName, iDOMParser, iDOMDoc, iDOMRootElement);
    }
    catch (HAException&)
    {
        cout.flush();
        cerr.flush();
        cerr << "Failed!" << endl;
        if( iDOMParser )
        {
            iDOMParser->resetDocumentPool();
            iDOMParser->release();
            iDOMParser = 0;
        }
        throw;
    }
    cout << "Done." << endl;

    // Then traverse the DOM tree and populate the containers:
    cout << "Initializing platform data for " << iPfVersion << "...";
    try {
        InitializeElements();
    }
    catch( HAException& )
    {
        cerr << "Failed." << endl;
        iDOMParser->resetDocumentPool();
        iDOMParser->release();
        iDOMParser = 0;
        throw;
    }
    cout << "Done." << endl;
    iDOMParser->resetDocumentPool();
    iDOMParser->release();
    iDOMParser = 0;    
    cout << "Platform " << iPfVersion << " successfully initialized from platform " << iVersionStr << " data!"  << endl << endl;
}

/**
 *
 */
bool PlatformData::AddComponent(Component* comp)
{
    return iCList.insert(make_pair<string, Component*>( comp->ID(), comp )).second;
}

/**
 *
 */
bool PlatformData::AddProject(Project* prj)
{
    if( iProjectsById.insert(make_pair<string, ComponentFile*>(prj->ID(), prj)).second == false )
        return false;

    return true;
}

/**
 *
 */
bool PlatformData::AddSource(Source* src)
{
    if( iSourcesById.insert(make_pair<string, ComponentFile*>(src->ID(), src)).second == false )
        return false;

    return true;
}

/**
 *
 */
bool PlatformData::AddHeader(Header* hdr)
{
    if( iHeadersById.insert(make_pair<string, ComponentFile*>(hdr->ID(), hdr)).second == false )
        return false;
        
    return true;
}

/**
 * Factory method for creating element objects.
 */
ParsedElement* PlatformData::CreateElement( XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node )
{
    const string elementType( toString( node->getNodeName() ));
    ParsedElement* elem = 0;

    if( elementType == PLATFORM_ELEMENT_COMPONENT )
    {
        elem = new Component();
    }                
    else if( elementType == PLATFORM_ELEMENT_PROJECT )
    {
        elem = new Project();            
    }        
    else if( elementType == PLATFORM_ELEMENT_SOURCE )
    {
        elem = new Source();            
    }

    return elem;
}

/**
 * Traverses through the DOM-tree and builds element objects.
 */
void PlatformData::InitializeElements()
{
    if( iDOMDoc == 0 || iDOMRootElement == 0)
        throw HAException(string("Platform ") + string(iPfVersion) + string(" initialization failed.\n"));
    DOMNodeIterator* domIter = iDOMDoc->createNodeIterator(iDOMRootElement, DOMNodeFilter::SHOW_ELEMENT, NULL, true);
    if( domIter == 0 )
        throw HAException(string("Platform ") + string(iPfVersion) + string(" initialization failed.\n"));
    DOMNode* root = domIter->getRoot();
    if( root )
    {
        const XMLCh* platformVersion = GetAttribute(root, KXMLPlatformVersion);
        if( platformVersion )
            iVersionStr = toString(platformVersion);
    }
    DOMNode* nodeIter = 0;
    ParsedElement* elem = 0;
    while( (nodeIter = domIter->nextNode()) != 0 )
    {
        elem = CreateElement(nodeIter);
        if( elem && elem->Initialize(nodeIter, this) == false )
        {
            delete elem;            
        }
    }

    domIter->release();
}

/**
 * 
 */
const CFileMap& PlatformData::HeadersById() const
{
    return iHeadersById;
}

/**
 * 
 */
const CFileMap& PlatformData::ProjectsById() const
{
    return iProjectsById;
}

/**
 * 
 */
CFileMap& PlatformData::ProjectsById()
{
    return iProjectsById;
}

/**
 * 
 */
const CFileMap& PlatformData::SourcesById() const
{
    return iSourcesById;
}

/**
 * Finds include paths defined in the projects belonging to the 
 * same component than the header.
 */
const vector<string>& PlatformData::IncludePathsForHeader(const string& headerID)
{
    CFileMap::const_iterator hdrIter = iHeadersById.find(headerID);
    if( hdrIter != iHeadersById.end() )
    {
        Header* hdrObj = dynamic_cast<Header*>(hdrIter->second);
        if( hdrObj )
            return IncludePathsForHeader(hdrObj);
    }

    return iDummyStringVector;
}

/**
 * Finds include paths defined in the projects belonging to the 
 * same component than the header.
 */
const vector<string>& PlatformData::IncludePathsForHeader(Header* hdrObj)
{
    if( hdrObj == 0 )
        return iDummyStringVector;

    // First try to find includes from the cache:
    const vector<string>* cached = hdrObj->CachedIncludePaths();
    if( cached )
    {
        return *cached;
    }
    
    auto_ptr<vector<string> > newVector(new vector<string>());        
    Component* comp = 0;

    if( (comp = hdrObj->GetComponent()) != 0 )
    {
        // First insert the include paths defined in component level:
        newVector->insert(newVector->end(), comp->IncludePaths().begin(),  comp->IncludePaths().end());

        const FileList& prjs = comp->Projects();
        for( FileList::const_iterator prj = prjs.begin(); prj != prjs.end(); ++prj )
        {
            Project* prjObj = dynamic_cast<Project*>(*prj);
            if( prjObj )
            {
                const vector<string>& iPaths = prjObj->IncludePaths();
                vector<string>::const_iterator ip = iPaths.begin();

                for( ; ip != iPaths.end(); ++ip )
                {
                    if( !IsObjectInVector(*newVector, *ip) )
                    {
                        newVector->push_back(*ip);
                    }
                }
            }
        }
    }

    const vector<string>& hdrIncs = hdrObj->IncludePaths();
    for( vector<string>::const_iterator i = hdrIncs.begin(); i != hdrIncs.end(); ++i )
    {
        if( !IsObjectInVector(*newVector, *i) )
        {
            newVector->push_back(*i);
        }
    }

    // variable to track whether project has been found
    bool found = false;
    // Find a project in the platform data which includes the header under analysis and
    // add all paths in the mmp file as dependencies before compilation. 
    for( CFileMap::const_iterator pIter = iProjectsById.begin(); pIter != iProjectsById.end() && !found; ++pIter )
    {
        //First iterate over projects
        Project* prj = dynamic_cast<Project*>(pIter->second);
        const FileList& src = prj->Sources();
        FileList::const_iterator sIter = src.begin();
        for(;sIter != src.end() && !found; ++sIter)
        {
            // then search each source include in individual projects
            Source* so = dynamic_cast<Source*>(*sIter);
            const vector<string>& inc = so->Includes();
            vector<string>::const_iterator iIter = inc.begin();
            for(;iIter != inc.end() && !found; ++iIter)
            {
                string::size_type dirEnd = (*iIter).find_last_of('/\\');
                // IF header found
                if( (dirEnd == string::npos && *iIter == hdrObj->FileName()) ||
                    (dirEnd != string::npos && string((*iIter).begin()+dirEnd+1, (*iIter).end()) == hdrObj->FileName()))
                {
                    const vector<string>& tmp = prj->IncludePaths();
					if( IsObjectInVector<string>(tmp, hdrObj->Path()) )
					{
						vector<string>::const_iterator str = tmp.begin();
						for(;str != prj->IncludePaths().end(); ++str)
						{
							// only include paths which are not already present
							if( !IsObjectInVector<string>(*newVector, *str) )
							{
								newVector->insert(newVector->end(), *str);
								found = true;
							}
						}
					}
                }
            }
        }
    }
    hdrObj->SetCachedIncludePaths(newVector.release());
    return *(hdrObj->CachedIncludePaths());
}

/**
 * Finds include directives used with this header when the header
 * is compiled. Algorithm finds the <code>Header</code> object using 
 * the given ID and then calls overloaded <code>IncludesForHeader</code> 
 * using the <code>Header</code> object.
 */
const vector<string>& PlatformData::IncludesForHeader( const string& headerID )
{
    CFileMap::const_iterator hdrIter = iHeadersById.find(headerID);
    if( hdrIter != iHeadersById.end() )
    {
        Header* hObj = dynamic_cast<Header*>(hdrIter->second);
        if( hObj )
            return IncludesForHeader(hObj);
    }
    return iDummyStringVector;
}

void PlatformData::IncludesFromSource(const Header* hObj, const Source* srcObj, vector<string>& includes) const
{
    const vector<string>& includeDirectives = srcObj->Includes();
    vector<string>::const_iterator inc = includeDirectives.begin();
    for( ; inc != includeDirectives.end(); ++inc )
    {
        string::size_type dirEnd = (*inc).find_last_of("/\\");

        if( (dirEnd == string::npos && *inc == hObj->FileName()) ||
            (dirEnd != string::npos && string(inc->begin()+dirEnd+1, inc->end()) == hObj->FileName()))
        {
            // The header was found. Take all the preceding include directives:
            for( vector<string>::const_iterator tempIt = includeDirectives.begin(); tempIt != inc; ++tempIt)
            {
                if( IsObjectInVector(includes, *tempIt) == false )
                {                            
                    includes.push_back(*tempIt);
                }        
            }
            break;
        }
    }
}

/**
 * Finds include directives used with this header when the header
 * is compiled. Algorithm find first all the projects belonging
 * to the same component than the given <code>Header</code> object.
 * Then it finds all the source files belonging to the projects.
 * Then it scans the source files and if a source file includes
 * this header, all the preceding include directives in that source
 * file are inserted to the result vector.
 *
 * An example:
 *
 * Header, id: epoc32/include/hdr1.h, belongs to component c, which
 * contains one project p.mmp. Project p.mmp contains two source files:
 * s1.cpp and s2.cpp. Source s1.cpp includes hdrX.h, hdrY.h and hdr1.h 
 * (in that order). Source s2.cpp does not include the hdr1.h at all.
 * The returned headers in above example would be hdrX.h and hdrY.h.
 */
const vector<string>& PlatformData::IncludesForHeader(Header* hObj, Header* baseHObj)
{
	string tempSpurceObj;
    if( hObj == 0 )
        return iDummyStringVector;

    if( hObj->CachedIncludes() != 0 )
        return *(hObj->CachedIncludes());

           
    // Start build new include list:
    auto_ptr<vector<string> > newVector(new vector<string>());        
    Component* comp = 0;

    if( (comp = hObj->GetComponent()) != 0 )
    {
        //set the forced header for this header
        hObj->SetCachedForcedInclude(comp->ForcedInclude());
        // Insert include directives defined in component level:
        newVector->insert(newVector->end(), comp->Includes().begin(), comp->Includes().end());

        // Then find all the sources that are including this header and get all the preceding include
        // directives from the sources. The shortest list will do.

        const FileList& projects = comp->Projects(); // All the projects in this component
        FileList::const_iterator fIter = projects.begin();

        // Get needed source files from the projects of this component:
        FileList srcObjs;
        for( ; fIter != projects.end(); ++fIter )
        {
            Project* prj = dynamic_cast<Project*>(*fIter);        
            if( prj )
            {                    
                srcObjs.insert(srcObjs.end(), prj->Sources().begin(), prj->Sources().end());
            }
        }

        // Next we investigate the include directives of each source file
        // and get all the headers that are included before the given 
        // header file.
        auto_ptr<vector<string> > includesFromSrc(0);
        for( FileList::iterator src = srcObjs.begin(); src != srcObjs.end(); ++src )
        {
            Source* srcObj = dynamic_cast<Source*>(*src);        
            if( srcObj == 0 )
                continue;

            const vector<string>& includeDirectives = srcObj->Includes();
            vector<string>::const_iterator inc = includeDirectives.begin();
            auto_ptr<vector<string> > tmpIncludes(new vector<string>());
           
            IncludesFromSource(hObj, srcObj, *tmpIncludes);
            if( includesFromSrc.get() == 0 ||
                (tmpIncludes->size() > 0 && (tmpIncludes->size() < includesFromSrc->size() || includesFromSrc->size()==0) ))
            {
				tempSpurceObj = srcObj->ID();
                includesFromSrc = tmpIncludes; // Get the smallest possible set of additional includes.
            }
        }
        if( includesFromSrc.get() )
        {
            newVector->insert(newVector->end(), includesFromSrc->begin(), includesFromSrc->end());
        }
    }

    if( newVector->size() == 0 )
    {
        // No includes found. Let's try to find some source from other components. First one will do...
        for( CFileMap::const_iterator s = iSourcesById.begin(); s != iSourcesById.end(); ++s )
        {
            auto_ptr<vector<string> > tmpIncludes(new vector<string>());
            Source* sO = dynamic_cast<Source*>(s->second);
            if( sO )
            {
                IncludesFromSource(hObj, sO, *tmpIncludes);
                if( tmpIncludes->size() > 0 )
				{
					string curSrc;
					string baseSrc;
					if ( baseHObj != NULL) // IncludesForHeader() is called for current sdk
					{
						string::size_type loc = sO->ID().find_last_of('/\\');
						if(loc != string::npos )
							curSrc = sO->ID().substr(loc+1 , string::npos);
						loc = string::npos;
						loc = baseHObj->CachedSource().find_last_of('/\\');
						if(loc != string::npos)
							baseSrc = baseHObj->CachedSource().substr(loc+1, string::npos);
					}
					// If the header is of baseline sdk or the current headers source file name is same as baseline's source file,
					// In both of these cases , the dependent headers will be taken from platform data file
					if(baseHObj == NULL || (baseSrc.size() > 0 && baseSrc == curSrc) )
					{
						newVector->insert(newVector->end(), tmpIncludes->begin(), tmpIncludes->end());
					}
					else // as current header's source file is not same as basiline's, so baseline's cacheinclude will be taken for current header too.
					{
						newVector->insert(newVector->end(), baseHObj->CachedIncludes()->begin(), baseHObj->CachedIncludes()->end());
					}
					break;
				}
            }
        }
    }    
    hObj->SetCachedIncludes(newVector.release());
	if(baseHObj == NULL) // IncludesForHeader() is called for baseline sdk, so get the source file name in cache
	{
		hObj->SetCachedSourceFile(tempSpurceObj);
	}
    return *(hObj->CachedIncludes());
}
/**
 *
 */
string PlatformData::PrettyPrint() const
{
    string ret("PLATFORM version: ");
    ret += iVersionStr + "\n";
   
    for( ComponentList::const_iterator c = iCList.begin(); c != iCList.end(); ++c )
    {
        ret += c->second->PrettyPrint();
    }
    return ret;
}

/**
 *
 */
const ComponentList& PlatformData::Components() const
{
    return iCList;
}

/**
 *
 */
const string& PlatformData::GetRootDir() const
{
    return iRootDir;
}
