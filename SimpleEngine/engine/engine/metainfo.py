# -*- coding: utf-8 -*-
# write by Liu Yiqi

import re
import pathlib

root_path = r"E:\Works\git_trunk\toolcenter\SimpleEngine\engine\engine"
target_dir = r"E:\Works\git_trunk\toolcenter\SimpleEngine\engine\engine\metainfo"
class_pattern = re.compile("class (?P<className>\w+) *:? *(public (?P<parentName>\w+))?\n{.*META_OBJECT.*}", re.M | re.S)
# 查找所有的.h文件，对于包含了QObject宏的类，初始化它的元对象信息
meta_info = '''#include "%s"\n\n
MetaObject %s::s_metaObject = MetaObject{ "%s", "%s", %d, %d};
'''
g_classID = 0
def getClassID():
    global g_classID
    g_classID += 1
    return g_classID


def getMetaCode(fileNameToClassName: dict):
    code = '''\
/********************************************
此文件由程序自动生成，请勿手动更改
********************************************/

#include<map>
#include<string>
 
#include"MetaObject.h"

// 包含头文件
%s

using namespace std;
// 元数据字典
map<string, MetaObject*> MetaObject::metaObjects = {
    %s
};'''
    includes = []
    items = []
    for fileName, className in fileNameToClassName.items():
        include = f'#include "{fileName}"'
        includes.append(include)
        item = f'pair<string, MetaObject*>("{className}", &{className}::s_metaObject)'
        items.append(item)
    include_code = "\n".join(includes)
    item_code = ",\n\t".join(items)
    code %= (include_code, item_code)
    return code


if __name__ == '__main__':
    classNameToID = {}
    fileNameToClassName = {}
    root = pathlib.Path(root_path)
    target_path = pathlib.Path(target_dir)
    if not target_path.exists():
        target_path.mkdir()
    for e in root.rglob("*.h"):
        with open(e) as fp:
            code = fp.read()
            res = class_pattern.search(code)
            if res:
                className = res.group('className')
                fileNameToClassName[e.name] = className
                classID = getClassID()
                classNameToID[className] = classID
                parentName = res.group('parentName') or ""
                parentID = classNameToID.get(parentName, -1)
                info = meta_info % (e.name, className, className, parentName, classID, parentID)
                fileName = f"meta_{e.stem}.cpp"
                filePath = target_path / fileName
                with open(filePath, "w") as metaFile:
                    metaFile.write(info)
    code = getMetaCode(fileNameToClassName)
    with open(target_path / "meta_ClassInfo.cpp", "w") as fp:
        fp.write(code)


