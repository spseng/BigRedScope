//
// NetworkHandler.cpp
//

#include "NetworkHandler.h"

NetworkHandler::NetworkHandler() {
    inst = nt::NetworkTableInstance::GetDefault();
}

NetworkHandler::NetworkHandler(const std::string &ipAddress) : NetworkHandler() {
    init(ipAddress);
}

void NetworkHandler::init(const std::string &ipAddress) {
    inst.StartClient4("dashboard");
    inst.SetServer(ipAddress.c_str());
}

// Double subscribers
void NetworkHandler::addDoubleSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName) {
    auto table = inst.GetTable(tableName);
    auto topic = table->GetDoubleTopic(topicName);
    doubleSubscribers[name] = topic.Subscribe(0.0);
}

double NetworkHandler::getDouble(const std::string &name, const double defaultValue) {
    if (!doubleSubscribers.contains(name)) {
        return defaultValue;
    }
    return doubleSubscribers[name].Get();
}

// Pose2d subscribers
void NetworkHandler::addPose2dSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName) {
    auto table = inst.GetTable(tableName);
    auto topic = table->GetStructTopic<frc::Pose2d>(topicName);
    pose2dSubscribers[name] = topic.Subscribe(frc::Pose2d{});
}

frc::Pose2d NetworkHandler::getPose2d(const std::string &name) {
    if (!pose2dSubscribers.contains(name)) {
        return frc::Pose2d{};
    }
    return pose2dSubscribers[name].Get();
}

// Translation2d subscribers
void NetworkHandler::addTranslation2dSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName) {
    auto table = inst.GetTable(tableName);
    auto topic = table->GetStructTopic<frc::Translation2d>(topicName);
    translation2dSubscribers[name] = topic.Subscribe(frc::Translation2d{});
}

frc::Translation2d NetworkHandler::getTranslation2d(const std::string &name) {
    if (!translation2dSubscribers.contains(name)) {
        return frc::Translation2d{};
    }
    return translation2dSubscribers[name].Get();
}

// Rotation2d subscribers
void NetworkHandler::addRotation2dSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName) {
    auto table = inst.GetTable(tableName);
    auto topic = table->GetStructTopic<frc::Rotation2d>(topicName);
    rotation2dSubscribers[name] = topic.Subscribe(frc::Rotation2d{});
}

frc::Rotation2d NetworkHandler::getRotation2d(const std::string &name) {
    if (!rotation2dSubscribers.contains(name)) {
        return frc::Rotation2d{};
    }
    return rotation2dSubscribers[name].Get();
}

// Translation3d subscribers
void NetworkHandler::addTranslation3dSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName) {
    auto table = inst.GetTable(tableName);
    auto topic = table->GetStructTopic<frc::Translation3d>(topicName);
    translation3dSubscribers[name] = topic.Subscribe(frc::Translation3d{});
}

frc::Translation3d NetworkHandler::getTranslation3d(const std::string &name) {
    if (!translation3dSubscribers.contains(name)) {
        return frc::Translation3d{};
    }
    return translation3dSubscribers[name].Get();
}

// Rotation3d subscribers
void NetworkHandler::addRotation3dSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName) {
    auto table = inst.GetTable(tableName);
    auto topic = table->GetStructTopic<frc::Rotation3d>(topicName);
    rotation3dSubscribers[name] = topic.Subscribe(frc::Rotation3d{});
}

frc::Rotation3d NetworkHandler::getRotation3d(const std::string &name) {
    if (!rotation3dSubscribers.contains(name)) {
        return frc::Rotation3d{};
    }
    return rotation3dSubscribers[name].Get();
}

// SwerveModuleState subscribers
void NetworkHandler::addSwerveModuleStateSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName) {
    auto table = inst.GetTable(tableName);
    auto topic = table->GetStructTopic<frc::SwerveModuleState>(topicName);
    swerveStateSubscribers[name] = topic.Subscribe(frc::SwerveModuleState{});
}

frc::SwerveModuleState NetworkHandler::getSwerveModuleState(const std::string &name) {
    if (!swerveStateSubscribers.contains(name)) {
        return frc::SwerveModuleState{};
    }
    return swerveStateSubscribers[name].Get();
}

// SwerveModuleState array subscribers
void NetworkHandler::addSwerveModuleStateArraySubscriber(const std::string &name, const std::string &tableName, const std::string &topicName) {
    auto table = inst.GetTable(tableName);
    auto topic = table->GetStructArrayTopic<frc::SwerveModuleState>(topicName);
    swerveStateArraySubscribers[name] = topic.Subscribe({});
}

std::vector<frc::SwerveModuleState> NetworkHandler::getSwerveModuleStateArray(const std::string &name) {
    if (!swerveStateArraySubscribers.contains(name)) {
        return {};
    }
    return swerveStateArraySubscribers[name].Get();
}

// Pose2d array subscribers
void NetworkHandler::addPose2dArraySubscriber(const std::string &name, const std::string &tableName, const std::string &topicName) {
    auto table = inst.GetTable(tableName);
    auto topic = table->GetStructArrayTopic<frc::Pose2d>(topicName);
    pose2dArraySubscribers[name] = topic.Subscribe({});
}

std::vector<frc::Pose2d> NetworkHandler::getPose2dArray(const std::string &name) {
    if (!pose2dArraySubscribers.contains(name)) {
        return {};
    }
    return pose2dArraySubscribers[name].Get();
}

// Check if subscriber exists
bool NetworkHandler::hasSubscriber(const std::string &name) const {
    return doubleSubscribers.contains(name) ||
           pose2dSubscribers.contains(name) ||
           translation2dSubscribers.contains(name) ||
           rotation2dSubscribers.contains(name) ||
           translation3dSubscribers.contains(name) ||
           rotation3dSubscribers.contains(name) ||
           swerveStateSubscribers.contains(name) ||
           swerveStateArraySubscribers.contains(name) ||
           pose2dArraySubscribers.contains(name);
}