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
import HTMLParser
import time
import sys
import os
import config


# Class that contains the Kevlar tool based API DB
class webAPIDB():
	def __init__(self):
		# Setting defaults values for URLs (= use S60 Kevlar tool)
		self.apiURL = "http://kevlar.nmp.nokia.com/kevlar/api/query/?"
		self.apiDataURL= "query_string="
		self.apitemp1URL="&header=on&release="
		self.apitemp2URL="&adaptation=Any&format=html"
		if config.API_REL_INDX == 0:
			self.apiData1URL = self.apitemp1URL + self.apitemp2URL
		else:
			self.apiData1URL = self.apitemp1URL + config.API_REL_INDX + self.apitemp2URL
		
		self.detailedAPIInfoURL = "http://trwww017.noe.nokia.com/cgi-bin/ifinfo/apidetails.pl?" 
		pass		
		
	# Default URLs can be changed using this function
	def setURLs(self, apiURL, apiDataURL, detailedAPIInfoURL):
		self.apiURL = apiURL
		self.apiDataURL= apiDataURL
		self.detailedAPIInfoURL = detailedAPIInfoURL
 	
 	# Function that get API info (name, category, etc.) from kevlar tool using header name is the search parameter		  
	def findAPIFromHeader(self, header):  
		success = 1
		retries = 0
		header = header.replace(' ','')
		while retries < 4:
			try:
				# Creating HTTP request
				data = self.apiURL + self.apiDataURL + header+self.apiData1URL
				
				req = urllib2.Request(data)		
				# Getting result
				result = urllib2.urlopen(req).read()
			except urllib2.URLError, e:
				if retries < 3:
					print "Network error, retrying"
					retries = retries + 1
					time.sleep(5)						
				else:
					if hasattr(e, 'reason'):
						print "We failed to reach a server."
						print e.reason

					elif hasattr(e, 'code'):
						print "The server couldn\'t fulfill the request."
						print e.code
					
					print "header name is"
					print header
					success = 0
					break
			except httplib.BadStatusLine, e:
				 print "HTTP Error, bad status line"
				 if hasattr(e, 'reason'):
						print e.reason

				 elif hasattr(e, 'code'):
						print e.code
				 print "header name is"
				 print header
				 success = 0
				 break
			else:
				 break
		# Parsing apiInfo from the HTML page
		detailinfo = []
		if success == 1:
			detailinfo = self.getAPIInfo(result)
		else:
			detailinfo.append("Network error")
			detailinfo.append("Network Error")

    		
		return detailinfo

	# Function that parses API info (name, category, etc.) from an HTML page 
	def getAPIInfo(self, result):
		apiInfo = []
		myparser = HTMLParser.HTMLParser()
		
		# Check did we get any matching APIs?
		if result.find('No results') == -1:
			
			myparser.parse(result)
			
			# Did we get only one matching API
			if myparser.getNumberOfAPIs() == 1:
				
				# First TD element contains the API name
				ApiName = myparser.get_descriptions()[0]
				SDKname = myparser.get_td_descriptions()[0]
				apiInfo.append(ApiName)
				apiInfo.append(SDKname)
				return apiInfo
			else:
				# Several matching APIs
				apiInfo.append("Several")
				apiInfo.append("Several")
				return apiInfo
		else:
			# No API was found => header file belongs to an unknown API TODO: Should this be done differently
			apiInfo.append("Unknown")
			apiInfo.append("Unknown")
			
			return apiInfo		