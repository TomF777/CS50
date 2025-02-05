-- write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred
SELECT title from people, stars, movies WHERE
    people.id = stars.person_id AND movies.id = stars.movie_id AND name = "Bradley Cooper" AND title IN (
SELECT title from people, stars, movies WHERE
    people.id = stars.person_id AND movies.id = stars.movie_id AND name = "Jennifer Lawrence"
);
