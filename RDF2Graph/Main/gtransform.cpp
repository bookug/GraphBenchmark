/*=============================================================================
# Filename: gtransform.cpp
# Author: Bookug Lobert 
# Mail: zengli-bookug@pku.edu.cn
# Last Modified: 2018-02-28 17:00
# Description: 
=============================================================================*/

#include "../Util/Util.h"
#include "../Database/Database.h"

using namespace std;

//[0]./gbuild [1]rdf_file_path [2]graph_file_path
int
main(int argc, char * argv[])
{
	//chdir(dirname(argv[0]));
//#ifdef DEBUG
	Util util;
//#endif
	if(argc < 3)  //./gbuild
	{
		//output help info here
		cout << "the usage of gtransform: " << endl;
		cout << "bin/gtransform rdf_file_path graph_file_path" << endl;
		return 0;
	}

	string _rdf = string(argv[1]);
	string _graph = string(argv[2]);
	Database _db(_rdf, _graph);
	bool flag = _db.transform();
	if (flag)
	{
		cout << "transform RDF file to graph done." << endl;
	}
	else
	{
		cout << "transform RDF file to graph failed." << endl;
	}
	
	//TODO: remove .db folder

	//system("clock");
	return 0;
}

