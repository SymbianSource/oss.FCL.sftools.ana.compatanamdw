#
# Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description:  Platform definitions container class
#

import urllib, sgmllib
import httplib, urllib2
import string

# Class that parses API information from HTTP output. Used by the WebAPIDB.py
class HTMLParser(sgmllib.SGMLParser):
    "A simple parser class."

    def parse(self, s):
        "Parse the given string 's'."
        self.feed(s)
        self.close()

    def __init__(self, verbose=0):
        "Initialise an object, passing 'verbose' to the superclass."
				
        sgmllib.SGMLParser.__init__(self, verbose)
        self.number_of_rows = 0
        self.hyperlinks = []
	self.descriptions = []
        self.inside_a_element = 0
	self.descriptions = []
        self.inside_td_element = 0
        self.tr_element_start = 0
	self.td_descriptions = []
	
	self.api_count = 0
	self.td_attribute = ('class', 'category')



    def start_a(self, attributes):
        "Process a hyperlink and its 'attributes'."
        
        for name, value in attributes:
            if name == "href":
                
                self.hyperlinks.append(value)
                
                if(value.find("/kevlar/api/UID_")) != -1:
                	self.api_count = self.api_count +1
                	self.inside_a_element = 1

    def end_a(self):
            "Record the end of a hyperlink."
            self.inside_a_element = 0

    def get_hyperlinks(self):
        "Return the list of hyperlinks."

        return self.hyperlinks

    def get_No_hyperlinks(self):
        "Return the no of hyperlinks."

        return len(self.hyperlinks)

    def handle_data(self, data):
    	"Handle the textual 'data'."
    	if self.inside_a_element:
    		self.descriptions.append(data)
    	if self.inside_td_element == 1:    		
    		# Check has tr element just started
    		if self.tr_element_start == 1:
    		  # If yes => We are in the first td element
    			self.tr_element_start = 0
    		if(data.find('domain') != -1):
    			data = "Domain"
    		elif(data.find('sdk') != -1):
    			data = "Sdk"
    		elif(data.find('platform') != -1):
    			data = "Platform"
    		elif(data.find('public') != -1):
    			data = "Public"
    		else:
    			data = "Unknown"
    		self.td_descriptions.append(data)
    		
    		
    		
    		

    def get_descriptions(self):
    	"Return a list of descriptions."
    	return self.descriptions

    def start_td(self, attributes):
    	
    	
    	if(self.td_attribute == attributes[0] ):
    		self.inside_td_element = 1

    def end_td(self):
    	self.inside_td_element = 0
    	
    def start_tr(self, attributes):
    	self.tr_element_start = 1
     	self.number_of_rows = self.number_of_rows + 1
     	
    def get_td_descriptions(self):
    	"Return a list of descriptions."
    	return self.td_descriptions
    	
    def getNumberOfAPIs(self):
    	return self.api_count