#ifndef __CEPGMANAGER_H__
#define __CEPGMANAGER_H__

#include <vector>
#include <map>
#include "CChannel.h"
#include "CEpgEvent.h"

class CEpgManager
{
public:
	// CEpgManager();
	// ~CEpgManager();

	static CEpgManager* getInstance(void);
	bool destoryInstance(void);

	bool start(Channel ch);
	bool update(Channel ch);
	bool stop(Channel ch);

	/**
	 * [获取对应频道的epg信息个数]
	 *
	 * @method getEventCount
	 *
	 * @param  ch            [查询的频道]
	 *
	 * @return               [获取到的epg event个数]
	 */
	unsigned int getEventCount(Channel ch);
	/**
	 * [根据传入的时间值获取对应频道的epg信息个数]
	 *
	 * @method getEventCount
	 *
	 * @param  ch            [查询的频道]
	 * @param  utcTime       [某个时间点]
	 *
	 * @return               [获取到的epg event个数]
	 */
	unsigned int getEventCount(Channel ch, unsigned long utcTime);
	/**
	 * [获取对应频道的所有epg信息]
	 *
	 * @method getEventAll
	 *
	 * @param  ch           [查询的频道]
	 * @param  events       [epg event信息]
	 *
	 * @return              [true==成功，false==失败]
	 */
	bool getEventAll(Channel ch, std::vector<EpgEvent>& events);
	/**
	 * [根据传入的个数值获取对应频道的epg信息]
	 *
	 * @method getEventAll
	 *
	 * @param  ch           [查询的频道]
	 * @param  needEpgCount [输入需要获取到的epg event个数；输出实际获取到的个数。]
	 * @param  events       [epg event信息]
	 *
	 * @return              [true==成功，false==失败]
	 */
	bool getEventAll(Channel ch, unsigned int& needEpgCount, std::vector<EpgEvent>& events);
	/**
	 * [根据传入的时间值及个数值获取对应频道的epg信息]
	 *
	 * @method getEventAll
	 *
	 * @param  ch           [查询的频道]
	 * @param  needEpgCount [输入需要获取到的epg event个数；输出实际获取到的个数。]
	 * @param  utcTime      [某个时间点]
	 * @param  events       [epg event信息]
	 *
	 * @return              [true==成功，false==失败]
	 */
	bool getEventAll(Channel ch, unsigned int& needEpgCount, unsigned long utcTime, std::vector<EpgEvent>& events);
	/**
	 * [获取epg pf信息]
	 *
	 * @method getEventPf
	 *
	 * @param  ch         [查询的频道]
	 * @param  events     [epg event信息]
	 *
	 * @return            [true==成功，false==失败]
	 */
	bool getEventPf(Channel ch, std::vector<EpgEvent>& events);

private:
	std::map<unsigned short, std::vector<EpgEvent> > epgAll;
};


#endif // __CEPGMANAGER_H__
