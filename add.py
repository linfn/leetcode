#!/usr/bin/env python3

import argparse
import json
import os
import re
import sys

import html2text
import requests

title = 'add-two-numbers'
arg_parser = argparse.ArgumentParser(
    description='Create a cpp solution template for the leetcode problem')
arg_parser.add_argument('problem', metavar='problem',
                        help='problem title or url. e.g. two-sum or https://leetcode.com/problems/two-sum/')
args = arg_parser.parse_args()

name = args.problem.strip()
m = re.match(r'(?:http|https):\/\/leetcode\.com\/problems\/([^/]+)\/?$', name)
name = m.group(1) if m else name.lower().replace(' ', '-')

resp = requests.post(
    'https://leetcode.com/graphql',
    headers={
        'pragma': 'no-cache',
        'cache-control': 'no-cache',
    },
    json={
        'operationName': 'questionData',
        'variables': {
            'titleSlug': name,
        },
        'query': """
            query questionData($titleSlug: String!) {
                question(titleSlug: $titleSlug) {
                    questionId
                    questionFrontendId
                    title
                    titleSlug
                    content
                    difficulty
                    topicTags {
                    name
                    slug
                    }
                    codeSnippets {
                    lang
                    langSlug
                    code
                    }
                    hints
                    sampleTestCase
                }
            }
        """
    },
)

assert resp.status_code >= 200 and resp.status_code < 300

question = resp.json()['data']['question']
#print(json.dumps(question, indent=4))

title_symbol = question['titleSlug'].lower().replace('-', '_')

h2t = html2text.HTML2Text()
h2t.strong_mark = ''
h2t.emphasis_mark = ''
content = h2t.handle(question['content']).strip()
content = re.sub(r'(Example(?: \d)?):\s*\n', '\g<1>:\n\n', content)

snippet = next(snip['code']
               for snip in question['codeSnippets'] if snip['langSlug'] == 'cpp')

test_method = None
solutionMatch = re.search(
    r'Solution(?:.|\n)*\S+\s+(\S+)\s*\(.*?\)', snippet)
if solutionMatch:
    test_method = solutionMatch.group(1)


template = f"""
/*
{question['title']}

URL: {f"https://leetcode.com/problems/{question['titleSlug']}"}
Tags: {[t['slug'] for t in question['topicTags']]}
___

{content}
*/

#include "test.h"

namespace {title_symbol} {{

inline namespace v1 {{
{snippet}
}} // namespace v1

TEST_CASE("{question['title']}") {{
    {f'TEST_SOLUTION({test_method}, v1) {{' if test_method else ''}
        {f"/*{question['sampleTestCase']}*/"}
    {'};' if test_method else ''}
}}

}} // namespace {title_symbol}
"""


os.makedirs('src', exist_ok=True)
filename = f"src/{question['questionFrontendId'].zfill(3)}_{title_symbol}.cpp"
if os.path.exists(filename):
    sys.exit(f'{filename} already exists')

with open(filename, 'w') as file:
    file.write(template)
