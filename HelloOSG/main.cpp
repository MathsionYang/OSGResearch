#include <iostream>
#include <Windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
using namespace std;
int main()
{
	//这里修改成OSG数据包里面的实例数据
	string osgPath = "F:\\OSGB365\\OSGData\\cow.osg";

	osgViewer::Viewer viewer;
	osg::Node* node = new osg::Node;
	node = osgDB::readNodeFile(osgPath);
	viewer.setSceneData(node);
	return viewer.run();
}