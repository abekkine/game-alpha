#!/usr/bin/python

import sys
from bitbucket.bitbucket import Bitbucket

Grn="\033[1;32m"
Red="\033[1;31m"
End="\033[0m"

args = sys.argv[1:]

if len(args) > 0:
    filtered = True
    status = args[0]
else:
    filtered = True
    status = u'new'

bb = Bitbucket('abekkine', 'daedalus_bb', repo_name_or_slug='gamealpha')

if filtered:
    if status == u'all':
        filter_params = {}
    else:
        filter_params = {
            'status' : status
        }
else:
    filter_params = {}

result, issues = bb.issue.all( params = filter_params )

if result:
    for issue in issues['issues']:
        state = issue['status']
        local_id = issue['local_id']
        title = issue['title']
        if state == 'new':
            mBegin = Red 
            mEnd = End
        elif state == 'resolved':
            mBegin = Grn
            mEnd = End
        else:
            mBegin = ""
            mEnd = ""
        print "#{id} [{mark_begin}{state}{mark_end}] {title}".format(
            id = local_id, 
            state = state, 
            title = title,
            mark_begin = mBegin,
            mark_end = mEnd )

