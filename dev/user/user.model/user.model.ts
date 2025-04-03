import { getPool } from "../../config/database/db.config";
import { userInfo } from "../user.dto/user.dto";

export const addnewUserModel = async(
    userInfo : userInfo
):Promise<number> => {
    const pool = await getPool();

    try {
        const query = `INSERT INTO user (nickname, password) VALUES (?, ?)`;

        const [result]:any = await pool.query(query, [userInfo.nickname, userInfo.password]);

        return result[0].userId;

    } catch (error : any) {
        throw new Error("쿼리문 에러" + error.message);
    }
};

export const getUserInfoModel = async (
    userId : number
):Promise<userInfo> => {
    const pool = await getPool();

    try {
        const query = `SELECT nickname, password FROM user WHERE userId = ?`;

        const [result]:any = await pool.query(query, [userId]);

        if(result.length === 0) {
            throw new Error("User가 존재하지 않습니다.");
        }

        return result[0] as userInfo;
    } catch (error : any) {
        throw new Error("쿼리문 에러" + error.message);
    }
};