select today.Id as Id from Weather today, Weather yestoday where today.Date = yestoday.date + interval 1 day and today.Temperature > yestoday.Temperature;
