/****************************************************************************
 * Notice:      Copyright (c) Skyworth.
 *              All rights reserved.
 * Owner:      miaolibin@skyworth.com
 ****************************************************************************/

#ifndef __CDATABASESERVICE_H__
#define __CDATABASESERVICE_H__

class CDatabaseService
{
public:
	CDatabaseService();
	~CDatabaseService();

        void DatabaseServiceSetDirtyByApplication(int16_t databaseIndex);
        
};

#endif  //__CDATABASESERVICE_H__
