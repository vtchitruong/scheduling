import os
import sys
from collections import deque
from prettytable import PrettyTable

input_file = os.path.join(sys.path[0], 'johnson_2_machines.inp')
output_file = os.path.join(sys.path[0], 'johnson_2_machines.out')


def input_data():
    with  open(input_file) as f:
        global n
        n = int(f.readline())

        global jobs
        jobs = []

        for i in range(n):
            j = tuple(map(int, f.readline().split()))
            jobs.append(j)


# Hàm tính tổng thời gian hoàn thành tất cả công việc
def calculate_time(J, S):
    global n

    start_1 = [0] * n
    finish_1 = [0] * n
    start_2 = [0] * n
    finish_2 = [0] * n

    # Thời điểm bắt đầu và kết thúc của công việc đầu tiên
    first_job = J[S[0] - 1]
    start_1[0] = 0
    finish_1[0] = first_job[1]
    start_2[0] = finish_1[0]
    finish_2[0] = start_2[0] + first_job[2]


    # Thời điểm bắt đầu và kết thúc của các công việc còn lại
    for i in range(1, n):
        current_job = J[S[i] - 1]

        start_1[i] = finish_1[i - 1]
        finish_1[i] = start_1[i] + current_job[1]

        start_2[i] = max(finish_1[i], finish_2[i - 1])
        finish_2[i] = start_2[i] + current_job[2]

    # Thời gian hoàn thành của công việc cuối cùng trên máy 2
    return finish_2[n - 1]


def process():
    # Phân nhóm
    # Nhóm 1: các công việc có time_1 <= time_2
    # Nhóm 2: các công việc có time_1 > time_2
    group_1 = []
    group_2 = []
    
    global jobs
    for job in jobs:
        if job[1] <= job[2]:
            group_1.append(job)
        else:
            group_2.append(job)

    # Sắp xếp nhóm 1 theo time_1 tăng dần
    group_1.sort(key=lambda x: x[1])

    # Sắp xếp nhóm 2 theo time_2 giảm dần
    group_2.sort(key=lambda x: x[2], reverse=True)

    # Lần lượt đưa nhóm 1 và nhóm 2 vào lịch
    global schedule
    schedule = []
    schedule = [i for i, _, _ in group_1] + [i for i, _, _ in group_2]

    # Tính tổng thời gian hoàn thành các công việc
    global total_time
    total_time = calculate_time(jobs, schedule)


def output():
    global schedule
    global total_time
    with open(output_file, 'w') as f:
        s = ' '.join([str(e) for e in schedule])        
        f.write(f'{s}\n')
        f.write(f'{total_time}')


if __name__ == '__main__':
    input_data()
    process()
    #show_arrays()    
    output()