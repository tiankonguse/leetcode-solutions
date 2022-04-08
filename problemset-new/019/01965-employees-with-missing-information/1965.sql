# Write your MySQL query statement below
select employee_id 
from  (select employee_id from Employees union all select employee_id from Salaries) A 
group by employee_id 
having count(*) = 1 
order by employee_id;


((select E.employee_id 
from Employees E left join Salaries S on E.employee_id = S.employee_id 
where S.salary is NULL)
union
(select S.employee_id 
from Employees E right join Salaries S on E.employee_id = S.employee_id 
where E.name is NULL))
ORDER BY employee_id