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


#ifndef CLASSNODEANALYSIS_H_
#define CLASSNODEANALYSIS_H_

#ifdef __WIN__
#pragma warning(disable:4786)
#endif
#include <xercesc/dom/DOM.hpp>
#include <vector>
#include <list>
#include <string>
#include "HANodeIterator.h"
#include "NodeAnalysis.h"
#include "NodeIndex.h"
#include "NodeTypeComparator.h"
using namespace std;

XERCES_CPP_NAMESPACE_USE



template <TIssueType IssueType>
void AddIssueClass(const HANodeIterator* self,TIssueIdentity classType, const HANodeIterator& ignorenode, int lineNo, 
				   const string& issueloc,const XMLCh* fileid=NULL)
{
	switch (classType)
	{
    case EIssueIdentityClass:
		AddIssue<EIssueIdentityClass,IssueType>(self,ignorenode,lineNo,issueloc,fileid);
		break;
    case EIssueIdentityStruct:
		AddIssue<EIssueIdentityStruct,IssueType>(self,ignorenode,lineNo,issueloc,fileid);
		break;
    case EIssueIdentityUnion:
		AddIssue<EIssueIdentityUnion,IssueType>(self,ignorenode,lineNo,issueloc,fileid);
		break;
	default:
		assert(false);
		break;

	};
}

template <TIssueType IssueType>
void AddIssueField(const HANodeIterator* self,TIssueIdentity classType, const HANodeIterator& ignorenode, int lineNo, 
				   const string& issueLoc, const XMLCh* fileid=NULL, const string name = "")
{
	switch (classType)
	{
    case EIssueIdentityField:
		AddIssue<EIssueIdentityField,IssueType>(self,ignorenode,lineNo,issueLoc,fileid,name);
		break;
    case EIssueIdentityFieldInaccessible:
		AddIssue<EIssueIdentityFieldInaccessible,IssueType>(self,ignorenode,lineNo,issueLoc,fileid, name);
		break;
	default:
		assert(false);
		break;

	};
}

/**
* Add issue field
* @param self pointer to self 
* @param classType type of issue 
* @param ignorenode reference to node
* @param fileid pointer to fileid 
* @param name reference to name
*/
template <TIssueType IssueType>
void AddIssueField(const HANodeIterator* self,TIssueIdentity classType, const HANodeIterator& ignorenode, int lineNo,
				   const string& issueLoc, const XMLCh* fileid, const DataMember & name)
{
	switch (classType)
	{
    case EIssueIdentityField:
		AddIssue<EIssueIdentityField,IssueType>(self,ignorenode,lineNo,issueLoc,fileid,name);
		break;
    case EIssueIdentityFieldInaccessible:
		AddIssue<EIssueIdentityFieldInaccessible,IssueType>(self,ignorenode,lineNo,issueLoc,fileid, name);
		break;
	default:
		assert(false);
		break;

	};
}


/**
* The member variables are analyzed for changes in order, type, removal, addition
* and visibility. Any change, including removal and addition, of the accessible
* data members of a class is reported.
*/
class ClassNodeAnalysis: public NodeAnalysis
{
public:

    static NodeAnalysis* Construct();
public:
    /**
    * Constructor
    */
    ClassNodeAnalysis();

    /**
    * Finds node to analyse it
    * @param baseline baseline node
    * @param current current node
    * @return 0, if there was no issues
    */
    int FindNodeAndAnalyse(HANodeIterator baseline,HANodeIterator current);

    /**
    * Analyse
    * @param baseline baseline node
    * @param current current node
    * @param report report or not (default= true)
    * @return 0, if there was no issues
    */
    int Analyse(HANodeIterator baseline,HANodeIterator current, bool report = true);

    /**
    * Destructor
    */
    ~ClassNodeAnalysis(){}


protected:
	   
    /**
    * Analyses fields
    * @param baseline baseline version
    * @param current current version
    * @param bfields base fields vector
    * @param cfields current fields vector 
    * @param report to report or not report issues
    * @return 0 if compared fields are equal
    */
	virtual int compareFields(HANodeIterator baseline,HANodeIterator current, 
                                                  const vector<DOMNode*>& bfields, const vector<DOMNode*>& cfields, 
                                                  bool report);

    /**
    * Analyses non-virtual functions 
    * @param baseline baseline version
    * @param current current version
    * @param bexportedMethods base exported methods vector
    * @param cexportedMethods current exported methods vector 
    * @param identity identity of the issue
    * @param report to report or not report issues
    * @return 0 if compared fields are equal
    */
    virtual int compareNonvirtualFunctions( HANodeIterator baseline,
                                            HANodeIterator current, 
                                            const vector<DOMNode*>& bexportedMethods, 
                                            const vector<DOMNode*>& cexportedMethods, 
                                            TIssueIdentity identity,
                                            bool report);

    // First bool for signature
    struct MethodMatchFlags
    {
        MethodMatchFlags(bool sM, bool rM) : signatureMatch(sM),returnValueMatch(rM){};
        bool signatureMatch;
        bool returnValueMatch;
        bool IsMatch() {return signatureMatch && returnValueMatch;};
    }; 
    
   /**
    * Analyses virtual functions 
    * @param baseline baseline version
    * @param current current version
    * @param bvirtualMethods base virtual methods vector
    * @param cvirtualMethods current virtual methods vector 
    * @param report to report or not report issues
    * @return 0 if compared fields are equal
    */
	virtual int compareVirtualFunctions(HANodeIterator baseline,HANodeIterator current, 
                                                  const vector<DOMNode*>& bvirtualMethods, 
												  const vector<DOMNode*>& cvirtualMethods, 
                                                  bool report);
   /**
    * Analyses other members
    * @param baseline baseline version
    * @param current current version
    * @param bothers base other items vector
    * @param cothers current other items vector 
    * @param report to report or not report issues
    * @return 0 if compared fields are equal
    */
	virtual int compareOthers(HANodeIterator baseline,HANodeIterator current, 
                                                  const vector<DOMNode*>& bothers, const vector<DOMNode*>& cothers, 
                                                  bool report);
	
    /**
    * Compares the base sizes of the classes
    * @param baseline to which to compare
    * @param current what to compare
    * @param bfields base data member table
    * @param cfields current data member table
    * @param report if true finding are reported
    * @return 0 if compared fields are equal
    */ 
	virtual int compareBaseSizes(HANodeIterator baseline, HANodeIterator current, const NodeIndex::dtable_t& bfields, const NodeIndex::dtable_t& cfields, bool report);			

protected:

    /**
    * Compares changes in inheritance
    * @param baseline to which to compare
    * @param current what to compare
    * @param report if true findings are reported
    * @return 0 if compared fields are equal
    */ 
    int compareBases(HANodeIterator baseline,HANodeIterator current, bool report);

    /**
    * Compares methods by function signature (return value is not involved)
    * @param basemethod basemethod to compare
    * @param currentmethod current to compare
    * @return true if signature isn't changed
    */
    bool compareMethodsSignature(HANodeIterator basemethod,HANodeIterator currentmethod, const NodeTypeComparator& comparator);
	
    /**
    * Compares all the members of the class
    * @param baseline baseline version
    * @param current current version
    * @param report if true findings are reported
    * @return 0 if there was no issues
    */
    int	compareClassMembers(HANodeIterator baseline,HANodeIterator current, bool report);

    /**
    * Analyses and reports the differences between two fields
    * @param basefield baseline field
    * @param currentfield current field
    * @param report if true findings are reported
    * @return 0 if compared fields are equal
    */
    //int compareField(HANodeIterator basefield,HANodeIterator currentfield, bool report);

    /**
    * Analyses and reports the differences between two fields
    * @param baseline baseline version
    * @param current current version
    * @param basemember base member to compare
    * @param currentmember current member to compare
    * @param report if true findings are reported
    * @return 0 if compared fields are equal
    */
	int compareField(HANodeIterator baseline, HANodeIterator current, const DataMember& basemember,const DataMember& currentmember, bool report);

    /**
    * Analyses the methods return value
    * @param basemethod baseline method
    * @param currentmethod current method
    * @return true if method returns are equal
    */
    bool compareMethodsReturn(HANodeIterator basemethod,HANodeIterator currentmethod,NodeTypeComparator& cmp);

    /**
    * Index virtual methods
    * @param node node to index
    * @param virtualMethods virtual methods in node
    * @param vtable virtual method table
    * @param virtualMethodsWithIndex methods indexed
    */
    void indexVirtualMethods(HANodeIterator node, 
											const vector<DOMNode*>& virtualMethods, 
											const NodeIndex::vtable_t& vtable,
											vector<pair<DOMNode*,int> >& virtualMethodsWithIndex);

    /**
    * Compare virtual methods
    * @param baseline baseline version
    * @param current current version
    * @param basevtable base virtual method table
    * @param currentvtable current virtual method table
    * @param report if true findings are reported
    */
    int compareVirtualTables(HANodeIterator baseline,HANodeIterator current,
											const NodeIndex::vtable_t& basevtable, 
											const NodeIndex::vtable_t& currentvtable,
                                            bool report);

    // Contains basemethod pointer and a boolean flag telling whether
    // the method was found in current methods or not.
    typedef map<DOMNode*, MethodMatchFlags> MethodMatchMap;
    virtual int compareNonvirtualFunctions( HANodeIterator baseline,
                                            HANodeIterator current, 
                                            const vector<DOMNode*>& bexportedMethods, 
                                            const vector<DOMNode*>& cexportedMethods, 
                                            TIssueIdentity identity,
								            bool report, 
                                            ComparatorVector::const_iterator comparator, 
                                            MethodMatchMap& baseMap,
                                            MethodMatchMap& currMap,
                                            int comparatorRound);

protected:

    //! To report added members
    bool iReportAddedMembers;
    //! Identity of the issue found
    TIssueIdentity iIdentity;
};

#endif
