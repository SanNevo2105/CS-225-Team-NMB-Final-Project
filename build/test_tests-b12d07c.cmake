add_test( [==[All available test cases:]==] /workspaces/CS-225-Team-NMB-Final-Project/build/test [==[All available test cases:]==])
set_tests_properties( [==[All available test cases:]==] PROPERTIES WORKING_DIRECTORY /workspaces/CS-225-Team-NMB-Final-Project/build)
add_test( [==[  Parsingdataset]==] /workspaces/CS-225-Team-NMB-Final-Project/build/test [==[  Parsingdataset]==])
set_tests_properties( [==[  Parsingdataset]==] PROPERTIES WORKING_DIRECTORY /workspaces/CS-225-Team-NMB-Final-Project/build)
add_test( [==[  Floyd-warshall]==] /workspaces/CS-225-Team-NMB-Final-Project/build/test [==[  Floyd-warshall]==])
set_tests_properties( [==[  Floyd-warshall]==] PROPERTIES WORKING_DIRECTORY /workspaces/CS-225-Team-NMB-Final-Project/build)
add_test( [==[2 test cases]==] /workspaces/CS-225-Team-NMB-Final-Project/build/test [==[2 test cases]==])
set_tests_properties( [==[2 test cases]==] PROPERTIES WORKING_DIRECTORY /workspaces/CS-225-Team-NMB-Final-Project/build)
set( test_TESTS [==[All available test cases:]==] [==[  Parsingdataset]==] [==[  Floyd-warshall]==] [==[2 test cases]==])
