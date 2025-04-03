import bcrypt from "bcrypt";

export const hashedPassword = async (
    password : string
):Promise<String> => {
    const salt = 10;
    const hashed = await bcrypt.hash(password, salt);

    return hashed;
};