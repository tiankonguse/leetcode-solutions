select A.event_day day,A.emp_id emp_id,sum(A.total_time) total_time 
from (select emp_id, event_day, in_time - out_time as total_time from Employees) A
group by A.emp_id, A.event_day;