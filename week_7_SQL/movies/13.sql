-- write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT name from people, stars, movies WHERE
    people.id = stars.person_id AND movies.id = stars.movie_id AND title IN (
SELECT DISTINCT title from people, stars, movies WHERE
    people.id = stars.person_id AND movies.id = stars.movie_id AND name = "Kevin Bacon" AND birth = 1958
) AND name IS NOT "Kevin Bacon";


