/**
 * Tencent is pleased to support the open source community by making Tseer available.
 *
 * Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
 * 
 * Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 * 
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software distributed 
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */

#ifndef __TSEER_API_LB_CONSISENT_HASH_
#define __TSEER_API_LB_CONSISENT_HASH_

#include <string>
#include <vector>
#include <set>
#include <map>
#include "lb.h"
#include "router_stat.h"
#include "TseerAgentComm.h"

namespace Tseerapi
{

class LBConsistentHash : public LoadBalance
{
public:
    LBConsistentHash();

    ~LBConsistentHash();

    virtual int addRouter(const Tseer::RouterNodeInfo& nodeInfo);

    virtual int getRouter(Tseer::RouterNodeInfo& nodeInfo, std::string &errMsg);

    virtual int getRouter(unsigned long long key, Tseer::RouterNodeInfo& nodeInfo, std::string &errMsg);

    virtual void clear();

    virtual int rebuild();

    virtual int statResult(const Tseer::RouterNodeInfo& req, int ret, int timeCost);

    virtual int del(const std::vector<Tseer::RouterNodeInfo> &nodeInfoVec);

private:

    bool checkActive(const Tseer::RouterNodeInfo& nodeInfo);

    unsigned int murmurHash32(const char *key, unsigned int len, unsigned int seed);

    CheckTimeoutInfo                    _checkTimeoutInfo;

    std::map<unsigned long long, RouterNodeStat>    _statMap;

    std::map<unsigned long long, Tseer::RouterNodeInfo> _normalMap;

    std::map<unsigned int, Tseer::RouterNodeInfo>    _tableMap;
};

}

#endif
