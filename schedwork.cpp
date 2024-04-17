#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool is_valid(
    const AvailabilityMatrix& avail,
    DailySchedule& sched,
    const size_t num_days,
    const size_t max_shifts,
    size_t day,
    Worker_T worker
);

bool backtrack(
    const AvailabilityMatrix& avail,
    DailySchedule& sched,
    const size_t num_days,
    const size_t num_workers,
    const size_t num_needed,
    const size_t max_shifts,
    size_t day,
    size_t idx_worker
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t num_needed,
    const size_t max_shifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    const size_t num_days = avail.size();
    const size_t num_workers = avail[0].size();

    sched.resize(num_days);

    return backtrack(avail, sched, num_days, num_workers, num_needed, max_shifts, 0, 0);
}


bool is_valid(
    const AvailabilityMatrix& avail,
    DailySchedule& sched,
    const size_t num_days,
    const size_t max_shifts,
    size_t day,
    Worker_T worker
) {
    if (!avail[day][worker] || find(sched[day].begin(), sched[day].end(), worker) != sched[day].end()) {
        return false;
    }

    size_t shift_cnt = 0;
    for (size_t d = 0; d < num_days; d++) {
        if (find(sched[d].begin(), sched[d].end(), worker) != sched[d].end()) {
            shift_cnt++;
        }
    }

    return shift_cnt < max_shifts;
}

bool backtrack(
    const AvailabilityMatrix& avail,
    DailySchedule& sched,
    const size_t num_days,
    const size_t num_workers,
    const size_t num_needed,
    const size_t max_shifts,
    size_t day,
    size_t idx_worker
) {
    size_t next_day = day;
    size_t next_idx_worker = idx_worker;

    bool end = false;
    if (idx_worker + 1 < num_needed) {
        next_idx_worker = idx_worker + 1;
    } else if (day + 1 < num_days) {
        next_idx_worker = 0;
        next_day = day + 1;
    } else {
        end = true;
    }

    for (Worker_T worker = 0; worker < num_workers; worker++) {
        if (is_valid(avail, sched, num_days, max_shifts, day, worker)) {
            sched[day].push_back(worker);
            if (end) {
                return true;
            }
            if (backtrack(avail, sched, num_days, num_workers, num_needed, max_shifts, next_day, next_idx_worker)) {
                return true;
            }
            sched[day].pop_back();
        }
    }

    return false;
}


