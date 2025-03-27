
find_package(CppJify)
create_jify_target(SimpleDatatypesDemo SimpleDatatypes.cpp out)
create_jify_jar(SimpleDatatypesDemoJar SimpleDatatypesDemo out CppJify)


