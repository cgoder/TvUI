
#ifndef  __PICTUREMENUEXECUTOR_H__
#define  __PICTUREMENUEXECUTOR_H__

#include "cocos2d.h"

#include <string>
#include <map>
using namespace std;

class PictureMenuExecutor
{
public:
	PictureMenuExecutor();
	~PictureMenuExecutor();
	
	void menuRelativeOptionCallbackFun(string& selectedItemMenuName, string& optionName);
	
	void PictureModeRefresh(void);
	void PictureOptionRefresh(void);
	
	std::map<string, string> m_picture_mode_refresh;
	std::map<string, int> m_ms_ui_picture;

private:
	class PriveteImpl;
	PriveteImpl* m_pImpl;
	
};


#endif //__PICTUREMENUEXECUTOR_H__

