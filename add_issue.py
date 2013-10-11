#!/usr/bin/python

import sys
from bitbucket.bitbucket import Bitbucket

bb = Bitbucket('abekkine', 'daedalus_bb', repo_name_or_slug='gamealpha')

args = sys.argv[1:]
issue_title = args[0]
issue_kind = args[1]

invalidKind = False
if issue_kind != u"bug":
    if issue_kind != u"task":
        invalidKind = True

if not invalidKind:
    bb.issue.create( title=issue_title, responsible=bb.username, status=u'new', kind=issue_kind)

