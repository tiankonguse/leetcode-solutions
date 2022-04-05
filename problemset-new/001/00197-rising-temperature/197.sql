# Write your MySQL query statement below
select today.Id as Id from Weather today, Weather yestoday where today.recordDate = yestoday.recordDate + interval 1 day and today.Temperature > yestoday.Temperature;
