CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  RETURN (
      # Write your MySQL query statement below.
      select t3.Salary from (select min(t2.Salary) as Salary, count(*) as Num from (select distinct t1.Salary as Salary from Employee t1 order by t1.Salary desc limit N) t2) t3 where t3.Num = N
  );
END
