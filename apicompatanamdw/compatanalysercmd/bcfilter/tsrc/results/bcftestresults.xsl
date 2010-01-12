<!-- 
- Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
- All rights reserved.
- This component and the accompanying materials are made available
- under the terms of the License "Eclipse Public License v1.0"
- which accompanies this distribution, and is available
- at the URL "http://www.eclipse.org/legal/epl-v10.html".
- 
- Initial Contributors:
- Nokia Corporation - initial contribution.
- 
- Contributors:
- 
- Description:
- 
-->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">

<HTML xmlns:msie="urn:default">
<msie:download id="dler" style="behavior:url(#default#download)"/>

<HEAD>
<TITLE>BCFilter Test Report</TITLE>
</HEAD>

<BODY bgColor="#f8f8f8">
<font size="5">Report Information</font><BR/><HR/>

<TABLE>
<TR>
<TD><i>Created</i></TD>
<TD>
<xsl:value-of select="testsuite/@timestamp"/>
</TD>
</TR>
<TR>
<TD><i>Failed test cases</i></TD>
<TD>
<xsl:value-of select="testsuite/@failures"/>/<xsl:value-of select="testsuite/@tests"/>
</TD>
</TR>

</TABLE>
<BR/><HR/>
<font size="5">Test case statuses</font><BR/><HR/>

<table width = "100%" cellpadding="0" cellspacing="0" bgColor="black" height="1"><tr><td></td></tr></table>
<table width = "100%" cellpadding="0" cellspacing="0" bgColor="#b0a8a0">
<tr><td><table width = "100%" cellpadding="3" cellspacing="1">
<tr bgcolor="#f0e8e0">
<TH align="left"><B>Test case</B></TH>
<TH align="left"><B>Expected</B></TH>
<TH align="left"><B>Actual</B></TH>
<TH align="left"><B>Status</B></TH>
</tr>
<xsl:for-each select="testsuite/testcase">
<xsl:variable name="cellbgcolour">
<xsl:choose>
<xsl:when test="count(failure) = 0">
<xsl:text>Green</xsl:text>
</xsl:when>
<xsl:otherwise>
<xsl:text>Red</xsl:text>
</xsl:otherwise>
</xsl:choose>
</xsl:variable>

<TR bgcolor= "White">
<TD><xsl:value-of select="@name"/></TD>
<TD><A><xsl:attribute name="href"><xsl:value-of select="expresults"/></xsl:attribute>Expected results</A></TD>
<TD><A><xsl:attribute name="href"><xsl:value-of select="actresults"/></xsl:attribute>Actual results</A></TD>
<xsl:if test="$cellbgcolour = 'Green'">
<TD bgcolor= "{$cellbgcolour}"><font color="White">PASSED</font></TD>
</xsl:if>
<xsl:if test="$cellbgcolour = 'Red'">
<TD bgcolor= "{$cellbgcolour}"><font color="White">FAILED</font></TD>
</xsl:if>

</TR>
</xsl:for-each>
</table></td></tr></table>

</BODY>
</HTML>
</xsl:template>
</xsl:stylesheet>
