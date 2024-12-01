create table t1 (
    k1  INTEGER PRIMARY key
);

create table t2 (
    k2 integer,
    FOREIGN key (k2) REFERENCES t1(k1)
    on update cascade
    on delete restrict
)

alter table t2 drop CONSTRAINT t2_k2_fkey;

alter table t2 set FOREIGN key (k2) REFERENCES t1(k1) on change cascase on delete restrict;

insert into t2 values (0),(1),(2);

drop table t2;

update t1
set k1 = 10
where k1 = 0;

select * from t2;