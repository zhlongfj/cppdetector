#pragma once
void IteratorRuleOutOfBoundDemo()
{
    std::vector<int> foo;
    for (unsigned int ii = 0; ii <= foo.size(); ++ii)
    {
        foo[ii] = 0;
    }
}

void IteratorRuleOutOfBoundDemo2()
{
    std::vector<int> foo;
    auto ss = foo.size();
    for (unsigned int ii = 0; ii <= ss; ++ii)
    {
        foo[ii] = 0;
    }
}

void IteratorRuleInvalidDereferenceDemo()
{
    std::vector<int>& ivec;
    std::vector<int>::iterator iter = ivec.begin();
    if (iter == ivec.end()){
        iter->value_type;
        cout << *iter;
    }
}

void IteratorRuleInvalidDereferenceDemo2()
{
    std::vector<int>& ivec;
    std::vector<int>::iterator iter = ivec.begin();
    if (ivec.find(3) == ivec.end())
    {
        ivec.find(3)->value_type;
        cout << *(ivec.find(3));
    }
}

DispatchOp* VSchedule::createChild(QObject* parentQml, int id)
{
    vector<ns::PlayTaskInfo>::iterator taskItemItor;
    if(id != SPOT_ID)
    {
        taskItemItor = std::find_if(m_pSolution->playTaskInfos.begin(), m_pSolution->playTaskInfos.end(), [id](const ns::PlayTaskInfo& item) {
            return item.taskItem.iId == id;
            });
        if (taskItemItor == m_pSolution->playTaskInfos.end())
        {
            //novaerror("idName is not found in the playTaskInfos, {}", idName.toStdString());
            return nullptr;
        }

        VTask* task = nullptr;
        if (taskItemItor->scheduleConstraints[0].constraint.bPlayByOnce)//预存节目
        {
            task = new VTaskPlayByOnce(parentQml, &taskItemItor->scheduleConstraints, id, nullptr);
            m_playByOnceTask = task;
            m_PlayByOnceTimer = std::make_shared<QTimer>();
            connect(m_PlayByOnceTimer.get(), &QTimer::timeout, this, &VSchedule::playByOnceSlotTimerOut);
            m_PlayByOnceTimer->start(SYNC_INTERVAL);
            novadebug("playByOnce start");
        }
	}
}