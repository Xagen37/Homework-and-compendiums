"use strict";

const cnst = (arg) => () => Number(arg);

const variable = name => (x, y, z) => {
    switch (name) {
        case "x": return Number(x);
        case "y": return Number(y);
        case "z": return Number(z);
    }
};

const sin = (arg) => (x, y, z) => Math.sin(arg(x, y, z));

const cos = (arg) => (x, y, z) => Math.cos(arg(x, y, z));

const pi = () => Math.PI;

const e = () => Math.E;

const add = (left, right) => (x, y, z) => left(x, y, z) + right(x, y, z);

const subtract = (left, right) => (x, y, z) => left(x, y, z) - right(x, y, z);

const multiply = (left, right) => (x, y, z) => left(x, y, z) * right(x, y, z);

const divide = (left, right) => (x, y, z) => left(x, y, z) / right(x, y, z);

const negate = arg => (x, y, z) => -arg(x, y, z);

function test() {
    let expr = add(
        subtract(
            multiply(
                variable("x"),
                variable("x")
            ),
            multiply(
                cnst(2),
                variable("x")
            )
        ),
        cnst(1)
    );

    for (let i = 0; i < 10; i++) {
        console.log(expr(i));
    }

};