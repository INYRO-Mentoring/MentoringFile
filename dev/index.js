"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
var express_1 = __importDefault(require("express"));
var dotenv_1 = __importDefault(require("dotenv"));
var cors_1 = __importDefault(require("cors"));
var app = (0, express_1.default)();
var router = express_1.default.Router();
var port = process.env.PORT || 3000;
dotenv_1.default.config();
app.use((0, cors_1.default)());
app.use(express_1.default.json());
app.use(express_1.default.urlencoded({ extended: true }));
app.use('dev');
app.use('/', function (res, req) {
    res.json('Iyniro Mentoring');
});
app.listen(port, function () {
    console.log("Server is running on port ".concat(process.env.PORT));
});
