-- write a SQL query to determine the average rating of all movies released in 2012.
SELECT AVG(rating) from ratings WHERE movie_id IN (SELECT id from movies WHERE year = 2012);
