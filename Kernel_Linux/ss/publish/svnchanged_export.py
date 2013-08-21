#-*- coding: utf-8 -*-
#!/usr/bin/env python

# ====================================================================
#
# svnchanged_export.py
#
# Export Files in a revision Range
# Usage: svnchanged_export.py -r beginRev:endRev --username user --password passwd url targetPath
# Author: Rock Sun( http://rocksun.cn )
# Site: http://rocksun.cn/svnchanged-export/
# ====================================================================

import pysvn # http://pysvn.tigris.org/
import getopt, sys, time, string
import os, urllib
from urlparse import urlparse

# Options by default
targetPath = "." # Current directory
username = ""
password = ""
url = ""

revision_min = pysvn.Revision( pysvn.opt_revision_kind.number, 0 )
revision_max = pysvn.Revision( pysvn.opt_revision_kind.head )
hasRevision = False

try:
    optlist, args = getopt.getopt (sys.argv[1:], "r:u:p:",
                                   ["revision=", "username=", "password="])
    if len(args) == 1 or len(args) == 2:
        url = args[0]
        if len(args) == 2:
            targetPath = args[1]
    else:
        raise Exception ("Input URL [targetPath]")
        
    for option, value in optlist:
        if option == "--username" or option == "-u":
            username = value            
        elif option == "--password" or option == "-p":
            password = value
        elif option == "--revision" or option == "-r":
            revision = value
            if string.find(value, ":") >= 0:
                (revision_min0, revision_max0) = string.split(value, ":")
                revision_min = pysvn.Revision( pysvn.opt_revision_kind.number, int(revision_min0) )
                if revision_max0 != "HEAD":
                    revision_max = pysvn.Revision( pysvn.opt_revision_kind.number, int(revision_max0) )
                hasRevision = True
            else:
                raise Exception ("Please Input revision range " + str(option))
        else:
            raise Exception ("Unknown option " + str(option))
            
    if hasRevision == False:
        raise Exception ("Please Input Revision Range -r min:max")
        
    urlObject = urlparse(url)
    if urlObject.scheme == 'http' or urlObject.scheme == 'https':
        url = urlObject.scheme+"://"+urlObject.netloc+urllib.quote(urlObject.path.decode(sys.stdin.encoding).encode('utf8'))
    else:
        url = unicode(url, sys.stdin.encoding)
    print sys.stdin.encoding
        
    if not url.endswith("/"):
        url = url + "/"        
        
except getopt.error, reason:
    raise Exception ("Usage: " + sys.argv[0] + ": " + str(reason))
    
    
def get_login( realm, user, may_save ):
    return True, username, password, False
   
print username+password+url+targetPath

client = pysvn.Client()
if username != "" and password != "":
    client.callback_get_login = get_login

summary = client.diff_summarize(url, revision_min, url, revision_max)
#print summary
for changed in summary:
    #path, summarize_kind, node_kind, prop_changed
    #for key in changed.iterkeys():
    #    print key 
    
    if pysvn.diff_summarize_kind.delete == changed['summarize_kind']:
      fullPath = targetPath+"/"+changed['path']   
      if os.path.exists(fullPath):
        os.remove(fullPath)
    
    if pysvn.diff_summarize_kind.added == changed['summarize_kind'] or pysvn.diff_summarize_kind.modified == changed['summarize_kind']:
        print changed['summarize_kind'], changed['path']
        if changed['node_kind'] == pysvn.node_kind.file:
            
            #uniPath = changed['path'].decode('utf8').encode()
            file_text = client.cat(url+urllib.quote(changed['path'].encode('utf8')), revision_max)
            
            fullPath = targetPath+"/"+changed['path']    
            dirPath = fullPath[0:fullPath.rfind("/")]      
            
            if not os.path.exists(dirPath):
                os.makedirs(dirPath)
                        
            f = open(fullPath,'wb')
            f.write(file_text)
            f.close
