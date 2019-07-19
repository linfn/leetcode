#!/usr/bin/env python3

import json
import os
import re
import sys

import html2text
import requests

filename = sys.argv[1]
print(f'dealing {filename}...')

name = re.match(r'src/\d*_(.*)\.cpp', filename)[1]
name = name.replace('_', '-')

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

h2t = html2text.HTML2Text()
h2t.strong_mark = ''
h2t.emphasis_mark = ''
content = h2t.handle(question['content']).strip()
content = re.sub(r'(Example(?: \d)?):\s*\n', '\g<1>:\n\n', content)

template = f"""/*
{question['title']}

URL: {f"https://leetcode.com/problems/{question['titleSlug']}"}
Tags: {[t['slug'] for t in question['topicTags']]}
___

{content}
*/"""

file = open(filename, 'r+')
text = file.read()
text = re.sub(r'/\*(?:\n|.)*?\*/', template, text, count=1)
#text = re.sub(r'TEST_CASE\(.*\)', f"TEST_CASE(\"{question['title']}\")", text)

file.seek(0)
file.write(text)
# truncate 的作用就是在当前位置截断文件, 这样以前旧的内容(还没有被覆盖的部分)就删除了
file.truncate()

file.close()
print(f'done {filename}')
