
#ifndef  __SOUNDMENUEXECUTOR_H__
#define  __SOUNDMENUEXECUTOR_H__

#include <string>
#include <map>
using namespace std;

class SoundMenuExecutor
{
public:
	SoundMenuExecutor();
	~SoundMenuExecutor();
	
	void menuRelativeOptionCallbackFun(string& selectedItemMenuName, string& optionName);
	
	void SoundSettingRefresh(void);
	void SoundModeRefresh(void);
	
	std::map<string, int> m_ms_ui_Sound;
	std::map<string, string> m_sound_setting;

private:
	class PriveteImpl;
	PriveteImpl* m_pImpl;
	
};


#endif //__SOUNDMENUEXECUTOR_H__

