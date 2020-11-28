CREATE TABLE cities (
    city TEXT PRIMARY KEY,
    longitude REAL NOT NULL,
    latitude REAL NOT NULL
);

CREATE TABLE cost (
    from_city TEXT,
    to_city TEXT,
    cost REAL NOT NULL,
    PRIMARY KEY (from_city, to_city),
    FOREIGN KEY (from_city) REFERENCES cities (city)
    ON UPDATE CASCADE
    ON DELETE CASCADE,
    FOREIGN KEY (to_city) REFERENCES cities (city)
    ON UPDATE CASCADE
    ON DELETE CASCADE
);

CREATE VIEW adjacency_list AS
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
