# Write your MySQL query statement below
select t1.FirstName as FirstName, t1.LastName as LastName, t2.City as City, t2.State as State from Person t1 left join Address t2 on t1.PersonId = t2.PersonId;
