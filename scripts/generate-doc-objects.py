import re

endings = re.compile(r"(\} (\w+)\;)") # Grabs } Object;
members = re.compile(r"((\s\w+){1,} [\*\w:]+\;\s)") # Grabs: type member_name;

with open("../include/framebot/objects.h") as f:
    content = f.read()

objects = list()

for match in endings.finditer(content):
    objects.append(match.group(2))

ms_content = endings.split(content)[::3]

obj_mbs = dict()

for i in range(len(objects)):
    obj_mbs[objects[i]] = list()
    for match in members.finditer(ms_content[i]):
        obj_mbs[objects[i]].append(match.group(1))

def normalize (member):
    return member[1:len(member)-2].replace(':1', '')

# print(endings.findall(content))
# print(len(objects), len(ms_content))
# print(ms_content[2])
# print(normalize(obj_mbs['Video'][1]))

with open("model.rst", "w") as f:
    for key in obj_mbs.keys():
        f.write("\n.. c:type:: {tname}\n".format(tname=key))

        for member in obj_mbs[key]:
            f.write("\n\t.. c:member:: {mname}\n".format(mname=normalize(member)))