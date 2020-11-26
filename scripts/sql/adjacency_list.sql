SELECT
    B.idx AS from_idx,
    C.idx AS to_idx,
    A.cost
FROM
    cost AS A JOIN
    (SELECT
        ROWID - 1 AS idx,
        city
    FROM
        cities)	AS B ON
    A.from_city = B.city JOIN
    (SELECT
        ROWID - 1 AS idx,
        city
    FROM
        cities)	AS C ON
    A.to_city = C.city;
