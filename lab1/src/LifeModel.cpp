#include "LifeModel.hpp"

#include <stdexcept>

void LifeModel::setObserver(ModelObserver* observer) {
    observer_ = observer;
}

const LifeState& LifeModel::state() const {
    return state_;
}

void LifeModel::setData(const LifeData& data) {
    for (int value : {data.talks, data.music, data.swearing}) {
        if (value < 0 || value > MaxCount)
            throw std::invalid_argument("Count outside 0..10000");
    }

    LifeState next;
    next.data = data;
    next.score = data.talks + 2 * data.music + 3 * data.swearing;
    next.earplugs = next.score >= 50;
    next.hasData = true;
    state_ = next;
    if (observer_)
        observer_->onModelChanged(state_);
}
