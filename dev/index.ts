import express from 'express';
import dotenv from 'dotenv';
import cors from 'cors';

import { Request, Response } from "express";
import userRouter  from './user/user.router'

const app = express();
const router = express.Router();
const port = process.env.PORT || 3000;
dotenv.config();

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.use('/', (req : Request, res : Response) => {
    res.json('Iyniro Mentoring');
});

app.use('/user', userRouter);


app.listen(port, () => {
    console.log(`Server is running on port ${process.env.PORT}`);
});