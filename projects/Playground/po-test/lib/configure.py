#! /usr/bin/env python
# -*- coding: utf-8 -*-
#
# file configure.py
# This file is part of LyX, the document processor.
# Licence details can be found in the file COPYING.


def checkFormatEntries(dtl_tools):  
    ''' Check all formats (\Format entries) '''
    checkViewerEditor('a Tgif viewer and editor', ['tgif'],
        rc_entry = [r'\Format tgif       obj     Tgif                   "" "%%"	"%%"	"vector"'])
    #
    checkViewerEditor('a FIG viewer and editor', ['xfig', 'jfig3-itext.jar', 'jfig3.jar'],
        rc_entry = [r'\Format fig        fig     FIG                    "" "%%"	"%%"	"vector"'])
