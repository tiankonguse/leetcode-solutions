# Write your MySQL query statement below

'1', 'A', '10000', '1', '0'
'2', 'B', '60000', '2', '0'
'3', 'C', '80000', '2', '0'
'4', 'D', '40000', '1', '0'
'5', 'E', '70000', '1', '0'
'6', 'F', '80000', '2', '1'
'7', 'G', '40000', '1', '1'
'8', 'H', '50000', '1', '0'
'9', 'I', '50000', '1', '1'


'1', 'A', '10000', '1', '0'
'2', 'B', '60000', '2', '0'
'3', 'C', '80000', '2', '0'
'4', 'D', '40000', '1', '0'
'5', 'E', '70000', '1', '0'
'8', 'H', '50000', '1', '0'

# Company, Programmer, Pay, rank
'1', 'E', '70000', '1'



'1', 'A', '10000', '1', '0'
'4', 'D', '40000', '1', '0'
'5', 'E', '70000', '1', '0'
'8', 'H', '50000', '1', '0'


select t3.CompanyName  as DepartmentId, t2.Name as Employee, t2.Salary as Salary from  Employee t2 inner join (SELECT t0.Salary as Salary, t0.DepartmentId  as DepartmentId, count(*) as Rank,t0.CompanyName as CompanyName FROM (SELECT distinct Salary , DepartmentId, Department.Name as CompanyName FROM Employee inner join Department on(Employee.DepartmentId = Department.Id)) t0 left join (SELECT distinct Salary , DepartmentId FROM Employee) t1 on(t0.DepartmentId = t1.DepartmentId and t0.Salary <= t1.Salary) group by t0.DepartmentId, t0.Salary having(count(*)<=3)) t3 on(t2.DepartmentId = t3.DepartmentId and t2.Salary = t3.Salary) order by t3.DepartmentId, t3.Rank;


select t4.Name  as Department, t2.Name as Employee, t2.Salary as Salary from  Department t4 inner join Employee t2 inner join (SELECT t0.Salary as Salary, t0.DepartmentId  as DepartmentId, count(*) as Rank FROM (SELECT distinct Salary , DepartmentId FROM Employee) t0 left join (SELECT distinct Salary , DepartmentId FROM Employee) t1 on(t0.DepartmentId = t1.DepartmentId and t0.Salary <= t1.Salary) group by t0.DepartmentId, t0.Salary having(count(*)<=3)) t3 on(t2.DepartmentId = t4.Id and t2.DepartmentId = t3.DepartmentId and t2.Salary = t3.Salary) order by t3.DepartmentId, t3.Rank; 


select distinct t6.Department as Department, t6.Employee as Employee, t6.Salary as Salary from (
select t5.Id as Id,t4.Id as DepartmentId, t4.Name as Department, t5.Name as Employee, t5.Salary as Salary from Department t4, Employee t5 where t4.Id = t5.DepartmentId) t6, (select t7.DepartmentId as DepartmentId,t7.Salary as Salary from (select t1.DepartmentId as DepartmentId, t1.Salary as Salary from (select min(Id) as Id, DepartmentId,Salary from Employee group by DepartmentId,Salary) t1 , (select min(Id) as Id, DepartmentId,Salary from Employee group by DepartmentId,Salary) t2 where t1.DepartmentId = t2.DepartmentId and t1.Salary <= t2.Salary GROUP BY t1.Id HAVING count(*) <= 3) t7 group by t7.DepartmentId,t7.Salary) t3 where  t6.DepartmentId = t3.DepartmentId and t6.Salary >= t3.Salary order by t6.DepartmentId, t6.Salary desc;