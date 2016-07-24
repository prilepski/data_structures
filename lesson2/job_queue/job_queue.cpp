#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  long long num_workers_;
  vector<long long> jobs_;

  vector<long long> assigned_workers_;
  vector<long long> start_times_;

  // members for optimal solution
  vector<long long> m_HeapJobs;
  long long m_HeapSize;
  vector<long long> m_HeapAssignedWorkers;
  vector<long long> m_HeapStartTimes;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }

/*    cout << "===============" << std::endl;

    for (long long i = 0; i < jobs_.size(); ++i) {
      cout << m_HeapAssignedWorkers[i] << " " << m_HeapStartTimes[i] << "\n";

    } */
  }

  void ReadData() {
    long long m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(long long i = 0; i < m; ++i)
      cin >> jobs_[i];
    m_HeapSize = 0;
    m_HeapAssignedWorkers.resize(m, -1);
    m_HeapStartTimes.resize(m, -1);
    m_HeapJobs.resize(m, -1);

  }


  long long GetTop(){
    if (m_HeapSize > 0)
      return m_HeapJobs[0];
    else
      return -1;
  }

  void RemoveTop(){
    if (m_HeapSize <= 0)
      return; // do nothing: out of boundaries

    m_HeapJobs[0] = m_HeapJobs[m_HeapSize - 1];
    m_HeapSize--;
    SiftDown(0);
  }

  void SiftDown(long long index){
    if (index < 0 || index >= m_HeapSize || m_HeapSize <= 0)
      return; // do nothing if element is outside of the boundaries

    long long minIndex;
    long long leftIndex;
    for (;;){
      minIndex = index;
      leftIndex = 2 * index + 1;
      if (leftIndex < m_HeapSize)
        if (jobs_[m_HeapJobs[leftIndex]] < jobs_[m_HeapJobs[minIndex]])
          minIndex = leftIndex;
        else if (jobs_[m_HeapJobs[leftIndex]] == jobs_[m_HeapJobs[minIndex]])
          if (m_HeapAssignedWorkers[m_HeapJobs[leftIndex]] < m_HeapAssignedWorkers[m_HeapJobs[minIndex]])
            minIndex = leftIndex;

      long long rightIndex = leftIndex + 1;
      if (rightIndex < m_HeapSize)
        if (jobs_[m_HeapJobs[rightIndex]] < jobs_[m_HeapJobs[minIndex]])
          minIndex = rightIndex;
        else if (m_HeapAssignedWorkers[m_HeapJobs[rightIndex]] < m_HeapAssignedWorkers[m_HeapJobs[minIndex]])
          minIndex = rightIndex;

      if (index != minIndex){
        long long tmp = m_HeapJobs[index];
        m_HeapJobs[index] = m_HeapJobs[minIndex];
        m_HeapJobs[minIndex] = tmp;
        index = minIndex; // reset index to Jobs sifting down
      }
      else
        break;
    }
  }

  void InsertElement(long long index){
    if ((m_HeapSize + 1) >= m_HeapJobs.size())
      return;

    m_HeapSize++;
    m_HeapJobs[m_HeapSize - 1] = index;

    SiftUp(m_HeapSize - 1);
  }

  void SiftUp(long long index){
    long long parentIndex = -1;
    while (index > 0){
      if (((index - 1) % 2) == 0)
        parentIndex = (index - 1) / 2;
      else
        parentIndex = (index - 2) / 2;

      if (jobs_[m_HeapJobs[index]] < jobs_[m_HeapJobs[parentIndex]]){
        long long tmp = m_HeapJobs[index];
        m_HeapJobs[index] = m_HeapJobs[parentIndex];
        m_HeapJobs[parentIndex] = tmp;
      }
      index = parentIndex;
    }
  }

  // Process jobs optimally
  void AssignJobsHeap(){
    if (num_workers_ <= 0)
      return;
    // go through every item in the job list to assigne a worker thread
    long long currTime = 0;
    for (long long i = 0; i < jobs_.size(); ++i){

      // check if heap is empty. INitialize all worker in this case
      if (!m_HeapSize){
        for (long long currWorker = 0; currWorker < num_workers_; ++currWorker){
          if ( i < jobs_.size()){
            // mark job i + currWorker as processed by currWorker
            m_HeapAssignedWorkers[i] = currWorker;
            // TODO: add job to heap
            InsertElement(i);
            m_HeapStartTimes[i] = currTime;
            i++; // move pointer to current job
          }
          else // we reached end of the job list. End procedure
            break;
        }
      }
      // here we have heap size of number of worker threads
      // pick element. This one is going to finish first
      long long currentTop = GetTop();
      long long currWorker = m_HeapAssignedWorkers[currentTop];
      RemoveTop(); // we rememebered item. Remove it from the heap
      // remember which thread process the job and add current time to job execution time
      m_HeapAssignedWorkers[i] = m_HeapAssignedWorkers[currentTop];
      jobs_[i] += jobs_[currentTop];
      m_HeapStartTimes[i] = jobs_[currentTop];
      InsertElement(i);
    }
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (long long i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (long long j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    //AssignJobsHeap();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
