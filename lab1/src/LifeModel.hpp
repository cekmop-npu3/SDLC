#pragma once

struct LifeData {
    int talks = 0;
    int music = 0;
    int swearing = 0;
};

struct LifeState {
    LifeData data;
    int score = 0;
    bool earplugs = false;
    bool hasData = false;
};

class ModelObserver {
public:
    virtual ~ModelObserver() = default;
    virtual void onModelChanged(const LifeState& state) = 0;
};

class LifeModel {
public:
    static constexpr int MaxCount = 10000;
    void setObserver(ModelObserver* observer);
    void setData(const LifeData& data);
    const LifeState& state() const;

private:
    LifeState state_;
    ModelObserver* observer_ = nullptr;
};
