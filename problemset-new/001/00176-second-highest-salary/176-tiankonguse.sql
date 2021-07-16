# Write your MySQL query statement below


select t3.SecondHighestSalary SecondHighestSalary from (select t1.Salary SecondHighestSalary from (select distinct(Salary) from Employee) t1 left join (select distinct(Salary) from Employee) t2 on t1.Salary <= t2.Salary group by t1.Salary having(count(*) = 2) union select null SecondHighestSalary) t3 limit 1;


SELECT
    (SELECT DISTINCT
            Salary
        FROM
            Employee
        ORDER BY Salary DESC
        LIMIT 1 OFFSET 1) AS SecondHighestSalary
;


SELECT
    IFNULL(
      (SELECT DISTINCT Salary
       FROM Employee
       ORDER BY Salary DESC
        LIMIT 1 OFFSET 1),
    NULL) AS SecondHighestSalary

select max(Salary) SecondHighestSalary 
from Employee
where Salary < (select max(Salary) from Employee)