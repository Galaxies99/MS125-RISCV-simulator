# include <vector>

# ifndef _PREDICTION_
  # define _PREDICTION_
  
class globalPrediction {
  private:
    vector <int> cnt[60];
    int successCount, totalCount;
  
  public:
    globalPrediction() {
      successCount = totalCount = 0;
      for (int i=0; i<60; ++i) cnt[i].clear();
    } 
    
    bool getPrediction(int id) {
      int ccnt = 0;
      for (int i=0; i<10 && i<cnt[id].size(); ++i) ccnt += cnt[id][i];
      if(ccnt < 0) return false;
      return true;
    } 
    
    inline void addResult(int id, bool result, bool success) {
      if(result) {
        if(cnt[id].size() < 10) cnt[id].push_back(1);
        else {
          for (int i=1; i<10; ++i) cnt[id][i-1] = cnt[id][i];
          cnt[id][9] = 1;
        }
      }
      else {
        if(cnt[id].size() < 10) cnt[id].push_back(-1);
        else {
          for (int i=1; i<10; ++i) cnt[id][i-1] = cnt[id][i];
          cnt[id][9] = -1;
        }
      }
      if(success) ++ successCount;
      ++ totalCount;
    }
    
    inline void out() {
      cout << "Success " << successCount << " times, total " << totalCount << " times.\n";
      cout << "Accuracy: " << (double)successCount / totalCount * 100 << "%.\n";
    }
};

# endif
