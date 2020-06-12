"use strict";

function Const(value) {
    this.value = value;
};
Const.prototype.evaluate = function () {
    return this.value;
};
Const.prototype.toString = function () {
    return this.value.toString();
};
Const.prototype.prefix = function () {
    return this.toString();
};

function Variable(name) {
    this.name = name;
};
Variable.prototype.evaluate = function (x, y, z) {
    switch (this.name) {
        case "x":
            return x;
        case "y":
            return y;
        case "z":
            return z;
        default:
            return undefined;
    }
};

Variable.prototype.toString = function () {
    return this.name;
};

Variable.prototype.prefix = function () {
    return this.toString();
};

const arity = new Map([
    ["no operation", 0],
    ["negate", 1],
    ["sinh", 1],
    ["cosh", 1],
    ["+", 2],
    ["-", 2],
    ["/", 2],
    ["*", 2],
    ["sum", "any"],
    ["avg", "any"]
]);

function Operation(operation, char, ...args) {
    this.values = args;
    this.operation = operation;
    this.char = char;
    this.arity = (arity.get(char) === "any") ? (args.length) : (arity.get(char));
};

Operation.prototype.evaluate = function (x, y, z) {
    let temp = [];
    for (let i = 0; i < this.arity; i++) {
        temp.push(this.values[i].evaluate(x, y, z));
    }
    return this.operation(temp);
};

Operation.prototype.toString = function () {
    let toReturn = this.values[0].toString();
    for (let i = 1; i < this.arity; i++) {
        toReturn += " " + this.values[i].toString();
    }
    toReturn += " " + this.char;
    return toReturn;
};

Operation.prototype.prefix = function () {
    let toReturn = "(" + this.char;
    for (let i = 0; i < this.arity; i++) {
        toReturn += " " + this.values[i].prefix();
    }
    if (this.arity === 0) {
        toReturn += " ";
    }
    toReturn += ")";
    return toReturn;
};

function UnaryOperation(value, operation, char) {
    Operation.call(this, operation, char, value);
};

UnaryOperation.prototype = Object.create(Operation.prototype);

function Negate(value) {
    UnaryOperation.call(this, value,
        function (args) {
            return -Number(args[0]);
        },
        "negate"
    );
};
Negate.prototype = Object.create(UnaryOperation.prototype);

function Sinh(value) {
    UnaryOperation.call(this, value,
        function (args) {
            return Math.sinh(Number(args[0]));
        },
        "sinh"
    );
};
Sinh.prototype = Object.create(UnaryOperation.prototype);

function Cosh(value) {
    UnaryOperation.call(this, value,
        function (args) {
            return Math.cosh(Number(args[0]));
        },
        "cosh"
    );
};
Cosh.prototype = Object.create(UnaryOperation.prototype);


function BinaryOperation(left, right, operation, char) {
    Operation.call(this, operation, char, left, right);
};
BinaryOperation.prototype = Object.create(Operation.prototype);

function Add(left, right) {
    BinaryOperation.call(this, left, right,
        function (args) {
            return Number(args[0]) + Number(args[1])
        },
        "+");
};
Add.prototype = Object.create(BinaryOperation.prototype);

function Subtract(left, right) {
    BinaryOperation.call(this, left, right,
        function (args) {
            return Number(args[0]) - Number(args[1])
        },
        "-");
};
Subtract.prototype = Object.create(BinaryOperation.prototype);

function Multiply(left, right) {
    BinaryOperation.call(this, left, right,
        function (args) {
            return Number(args[0]) * Number(args[1])
        },
        "*");
};
Multiply.prototype = Object.create(BinaryOperation.prototype);

function Divide(left, right) {
    BinaryOperation.call(this, left, right,
        function (args) {
            return Number(args[0]) / Number(args[1])
        },
        "/");
};
Divide.prototype = Object.create(BinaryOperation.prototype);

function Sum(...args) {
    Operation.call(this,
        function (args) {
            return args.reduce((accumulator, currentValue) => accumulator + currentValue, 0);
        },
        "sum",
        ...args);
};
Sum.prototype = Object.create(Operation.prototype);

function Avg(...args) {
    Operation.call(this,
        function (args) {
            return args.reduce((accumulator, currentValue) => accumulator + currentValue, 0) / args.length;
        },
        "avg",
        ...args);
}

Avg.prototype = Object.create(Operation.prototype);

const operations = new Map([
        ["+", Add],
        ["-", Subtract],
        ["/", Divide],
        ["*", Multiply],
        ["negate", Negate],
        ["sum", Sum],
        ["avg", Avg]
    ]
);

const errors = function () {
    function ParseError(message) {
        this.message = message;
    }

    ParseError.prototype = Object.create(Error.prototype);
    ParseError.prototype.constructor = ParseError;
    ParseError.prototype.name = "parseError";

    function BracketsMismatchError(message) {
        this.message = message;
    }

    BracketsMismatchError.prototype = Object.create(ParseError.prototype);
    BracketsMismatchError.prototype.constructor = BracketsMismatchError;
    BracketsMismatchError.prototype.name = "BracketsMismatchError";

    function InvalidSyntaxError(message) {
        this.message = message;
    }

    InvalidSyntaxError.prototype = Object.create(ParseError.prototype);
    InvalidSyntaxError.prototype.constructor = InvalidSyntaxError;
    InvalidSyntaxError.prototype.name = "InvalidSyntaxError";

    function InvalidOperationSyntaxError(message) {
        this.message = message;
    }

    InvalidOperationSyntaxError.prototype = Object.create(InvalidSyntaxError.prototype);
    InvalidOperationSyntaxError.prototype.constructor = InvalidOperationSyntaxError;
    InvalidOperationSyntaxError.prototype.name = "InvalidOperationSyntaxError";

    function ArgumentMismatchError(message) {
        this.message = message;
    }

    ArgumentMismatchError.prototype = Object.create(ParseError.prototype);
    ArgumentMismatchError.prototype.constructor = ArgumentMismatchError;
    ArgumentMismatchError.prototype.name = "ArgumentMismatchError";

    return {
        ParseError: ParseError,
        BracketsMismatchError: BracketsMismatchError,
        InvalidSyntaxError: InvalidSyntaxError,
        InvalidOperationSyntaxError: InvalidOperationSyntaxError,
        ArgumentMismatchError: ArgumentMismatchError
    };
}();

function parsePrefix(string) {
    let pos = 0;

    function parser(balance) {
        let content = [];
        let hasOp = false;
        while (pos < string.length) {
            skipWhitespace();
            switch (string[pos]) {
                case "(": {
                    pos++;
                    content.push(parser(balance + 1));
                    break;
                }
                case ")": {
                    if (balance <= 0) {
                        throw new errors.BracketsMismatchError("Missing opening parenthesis: " + string);
                    }
                    pos++;
                    return parseOp(content);
                }
                default: {
                    let token = getToken();
                    if (operations.has(token)) {
                        if (hasOp) {
                            throw new errors.InvalidOperationSyntaxError("Met more than one operation symbol: " + string);
                        } else {
                            content.push(token);
                            hasOp = true;
                        }
                    } else {
                        content.push(parseValue(token));
                    }
                }
            }
            skipWhitespace();
        }
        if (content.length !== 1) {
            throw new errors.InvalidSyntaxError("Invalid syntax: " + string);
        } else if (balance > 0) {
            throw new errors.BracketsMismatchError("Missing closing parenthesis: " + string);
        }

        return content[0];
    };

    function parseOp(content) {
        let op;
        if (operations.has(content[0])) {
            op = content[0];
        } else {
            throw new errors.InvalidOperationSyntaxError("Operation syntax for not operation: " + string);
        }
        return wrap(op, ...content.slice(1));
    };

    function parseValue(token) {
        if (isVariable(token)) {
            return new Variable(token);
        } else if (Number.isInteger(+token)) {
            return new Const(+token);
        } else {
            throw new errors.InvalidSyntaxError("Unknown character '" + token + "':" + string);
        }
    };

    function skipWhitespace() {
        while (string[pos] === " ") {
            pos++;
        }
    };

    function getToken() {
        let buffer = "";
        while (pos < string.length && string[pos] !== " " && string[pos] !== ")" && string[pos] !== "(") {
            buffer += string[pos++];
        }
        return buffer;
    };

    function wrap(op, ...args) {
        //console.log(op + " --- " + args);
        if (arity.get(op) !== "any" && args.length !== arity.get(op)) {
            throw new errors.ArgumentMismatchError("Invalid number of arguments for operation '" + op + "'. Expected " +
                arity.get(op) + ", got " + args.length);
        }
        return new (operations.get(op))(...args);
    };

    function isVariable(char) {
        return char === "x" || char === "y" || char === "z";
    };

    return parser(0);
};