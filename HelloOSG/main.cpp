#include <iostream>
#include <Windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
using namespace std;
int main()
{
	//�����޸ĳ�OSG���ݰ������ʵ������
	string osgPath = "F:\\OSGB365\\OSGData\\cow.osg";

	osgViewer::Viewer viewer;
	osg::Node* node = new osg::Node;
	node = osgDB::readNodeFile(osgPath);
	viewer.setSceneData(node);
	return viewer.run();
}