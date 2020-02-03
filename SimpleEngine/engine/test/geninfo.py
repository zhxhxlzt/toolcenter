# -*- coding: utf-8 -*-
# write by Liu Yiqi

import sys
import os
import re
import pathlib


target_dir = r"E:\Works\git_trunk\toolcenter\SimpleEngine\engine\test\autogen"
project_dir = r"E:\Works\git_trunk\toolcenter\SimpleEngine\engine\test"

class_pattern = re.compile("class (?P<className>\w+) *:? *(public (?P<parentName>\w+))?.*{.*Q_OBJECT.*}", re.M | re.S)
# 查找所有的.h文件，对于包含了QObject宏的类，初始化它的元对象信息

root = pathlib.Path(project_dir)

for e in root.rglob("*.h"):
    with open(e) as fp:
        code = fp.read()
        res = class_pattern.search(code)
        if res:
            className = res.group('className')
            parentName = res.group('parentName') or ""
            info = '''#include "%s"
MetaObject %s::_metaObject = MetaObject{ "%s", "%s" };      
            ''' % (e.name, className, className, parentName)
            fileName = f"Auto_{className}.cpp"
            filePath = pathlib.Path(target_dir) / fileName
            with open(filePath, "w") as autoFile:
                autoFile.write(info)


