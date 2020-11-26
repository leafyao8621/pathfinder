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
    FOREIGN KEY (from_city) REFERENCES cities (city),
    FOREIGN KEY (to_city) REFERENCES cities (city)
);
