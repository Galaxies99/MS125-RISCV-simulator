# include <vector>

# ifndef _PREDICTION_
  # define _PREDICTION_
  
class globalPrediction {
  private:
    std :: vector <int> cnt[60];
    int successCount, totalCount;
    double base[10];
      
  public:
    globalPrediction() {
      successCount = totalCount = 0;
      for (int i=0; i<60; ++i) cnt[i].clear();
      base[0] = 0.30, 
      base[1] = 0.40,
      base[2] = 0.50,
      base[3] = 0.60,
      base[4] = 0.73,
      base[5] = 0.8,
      base[6] = 0.85,
      base[7] = 0.9,
      base[8] = 0.95,
      base[9] = 1.0;
    } 
    
    bool getPrediction(int id) {
      double ccnt = 0;
      for (int i=0; i<10 && i<cnt[id].size(); ++i) ccnt += base[i] * cnt[id][i];
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
