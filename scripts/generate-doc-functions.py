import re

fname = re.compile(r"\w+\s\*{0,1}\s{0,1}\w+\*{0,1}\s{0,1}\(")

def clean (content):
    return content.replace("\n", "").replace("    ", " ")
    # return content

with open('../include/framebot/objects.h') as f:
    content = f.read()

    names = fname.findall(content)
    dump = list()

    for name in names:
        tmp = content.split(name)
        params = tmp[1].split(");")[0]
        dump.append("{}{})".format(name, clean(params)))

with open('../include/framebot/framebot.h') as f:
    content = f.read().split("#include <framebot/util.h>")[1]

    names = fname.findall(content)
    # dump = list()

    for name in names:
        tmp = content.split(name)
        params = tmp[1].split(");")[0]
        dump.append("{}{})".format(name, clean(params)))

with open('functions.rst', 'w') as f:
    for func in dump:
        f.write(".. c:function:: {}\n\n".format(func))