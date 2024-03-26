create table t1 (
    k1 int,
    primary key k1,
);

create table t2 (
    k1 int primary key,
    constraint c1 foreign key (k1) references t1(k1),
);
