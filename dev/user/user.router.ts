import { Router } from 'express';
import { addnewUserContorller, deleteUserController, getUserInfoController } from './user.controller/user.controller';

const router = Router();

router.post('/addNewUser', addnewUserContorller);
router.get('/getUserInfo', getUserInfoController);
router.delete('/deleteUser', deleteUserController);

/**
 * @swagger
 * /user/addNewUser:
 *   post:
 *     tags:
 *       - User
 *     summary: Add a new user
 *     description: Creates a new user with a nickname and password.
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             type: object
 *             required:
 *               - nickname
 *               - password
 *             properties:
 *               nickname:
 *                 type: string
 *                 example: exampleUser
 *               password:
 *                 type: string
 *                 example: securePassword123
 *     responses:
 *       200:
 *         description: User successfully created
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 successMessage:
 *                   type: string
 *                   example: "User created with ID: 123"
 *       404:
 *         description: Missing required fields
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 errorMessage:
 *                   type: string
 *                   example: Nickname is required.
 *       500:
 *         description: Internal server error
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 errorMessage:
 *                   type: string
 *                   example: An unexpected server error occurred.
 */

/**
 * @swagger
 * /user/getUserInfo:
 *   get:
 *     tags:
 *       - User
 *     summary: Get user info
 *     description: Returns user information based on the provided user ID.
 *     parameters:
 *       - in: query
 *         name: userId
 *         schema:
 *           type: integer
 *         required: true
 *         description: The ID of the user to retrieve.
 *         example: 123
 *     responses:
 *       200:
 *         description: Successfully retrieved user info
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 successMessage:
 *                   type: string
 *                   example: User info retrieved successfully.
 *       400:
 *         description: Missing or invalid userId, or user not found
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 errorMessage:
 *                   type: string
 *                   example: Missing or invalid userId.
 *       500:
 *         description: Internal server error
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 errorMessage:
 *                   type: string
 *                   example: An unexpected server error occurred.
 */

/**
 * @swagger
 * /user/deleteUser:
 *   delete:
 *     tags:
 *       - User
 *     summary: Delete a user
 *     description: Deletes a user based on the provided user ID.
 *     parameters:
 *       - in: query
 *         name: userId
 *         schema:
 *           type: integer
 *         required: true
 *         description: The ID of the user to delete.
 *         example: 123
 *     responses:
 *       202:
 *         description: User successfully deleted
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 successMessage:
 *                   type: string
 *                   example: User with ID 123 deleted successfully.
 *       400:
 *         description: Missing or invalid userId
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 errorMessage:
 *                   type: string
 *                   example: Missing userId.
 *       500:
 *         description: Server error while deleting user
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 errorMessage:
 *                   type: string
 *                   example: Internal server error occurred.
 */

export default router;